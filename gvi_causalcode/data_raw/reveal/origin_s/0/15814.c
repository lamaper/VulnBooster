gcry_error_t gcry_pk_genkey ( gcry_sexp_t * r_key , gcry_sexp_t s_parms ) {
 gcry_pk_spec_t * pubkey = NULL ;
 gcry_module_t module = NULL ;
 gcry_sexp_t list = NULL ;
 gcry_sexp_t l2 = NULL ;
 gcry_sexp_t l3 = NULL ;
 char * name = NULL ;
 size_t n ;
 gcry_err_code_t rc = GPG_ERR_NO_ERROR ;
 int i , j ;
 const char * algo_name = NULL ;
 int algo ;
 const char * sec_elems = NULL , * pub_elems = NULL ;
 gcry_mpi_t skey [ 12 ] ;
 gcry_mpi_t * factors = NULL ;
 gcry_sexp_t extrainfo = NULL ;
 unsigned int nbits = 0 ;
 unsigned long use_e = 0 ;
 skey [ 0 ] = NULL ;
 * r_key = NULL ;
 REGISTER_DEFAULT_PUBKEYS ;
 list = gcry_sexp_find_token ( s_parms , "genkey" , 0 ) ;
 if ( ! list ) {
 rc = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 l2 = gcry_sexp_cadr ( list ) ;
 gcry_sexp_release ( list ) ;
 list = l2 ;
 l2 = NULL ;
 if ( ! list ) {
 rc = GPG_ERR_NO_OBJ ;
 goto leave ;
 }
 name = _gcry_sexp_nth_string ( list , 0 ) ;
 if ( ! name ) {
 rc = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 module = gcry_pk_lookup_name ( name ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 gcry_free ( name ) ;
 name = NULL ;
 if ( ! module ) {
 rc = GPG_ERR_PUBKEY_ALGO ;
 goto leave ;
 }
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 algo = module -> mod_id ;
 algo_name = pubkey -> aliases ? * pubkey -> aliases : NULL ;
 if ( ! algo_name || ! * algo_name ) algo_name = pubkey -> name ;
 pub_elems = pubkey -> elements_pkey ;
 sec_elems = pubkey -> elements_skey ;
 if ( strlen ( sec_elems ) >= DIM ( skey ) ) BUG ( ) ;
 l2 = gcry_sexp_find_token ( list , "rsa-use-e" , 0 ) ;
 if ( l2 ) {
 char buf [ 50 ] ;
 const char * s ;
 s = gcry_sexp_nth_data ( l2 , 1 , & n ) ;
 if ( ! s || n >= DIM ( buf ) - 1 ) {
 rc = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 memcpy ( buf , s , n ) ;
 buf [ n ] = 0 ;
 use_e = strtoul ( buf , NULL , 0 ) ;
 gcry_sexp_release ( l2 ) ;
 l2 = NULL ;
 }
 else use_e = 65537 ;
 l2 = gcry_sexp_find_token ( list , "nbits" , 0 ) ;
 if ( l2 ) {
 char buf [ 50 ] ;
 const char * s ;
 s = gcry_sexp_nth_data ( l2 , 1 , & n ) ;
 if ( ! s || n >= DIM ( buf ) - 1 ) {
 rc = GPG_ERR_INV_OBJ ;
 goto leave ;
 }
 memcpy ( buf , s , n ) ;
 buf [ n ] = 0 ;
 nbits = ( unsigned int ) strtoul ( buf , NULL , 0 ) ;
 gcry_sexp_release ( l2 ) ;
 l2 = NULL ;
 }
 else nbits = 0 ;
 rc = pubkey_generate ( module -> mod_id , nbits , use_e , list , skey , & factors , & extrainfo ) ;
 gcry_sexp_release ( list ) ;
 list = NULL ;
 if ( rc ) goto leave ;
 {
 char * string , * p ;
 size_t nelem = 0 , nelem_cp = 0 , needed = 0 ;
 gcry_mpi_t mpis [ 30 ] ;
 int percent_s_idx = - 1 ;
 nelem = strlen ( pub_elems ) + strlen ( sec_elems ) ;
 if ( factors ) {
 for ( i = 0 ;
 factors [ i ] ;
 i ++ ) nelem ++ ;
 }
 nelem_cp = nelem ;
 needed += nelem * 10 ;
 needed += 2 * strlen ( algo_name ) + 300 + 5 ;
 if ( nelem > DIM ( mpis ) ) BUG ( ) ;
 nelem = 0 ;
 string = p = gcry_malloc ( needed ) ;
 if ( ! string ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 p = stpcpy ( p , "(key-data" ) ;
 p = stpcpy ( p , "(public-key(" ) ;
 p = stpcpy ( p , algo_name ) ;
 for ( i = 0 ;
 pub_elems [ i ] ;
 i ++ ) {
 * p ++ = '(' ;
 * p ++ = pub_elems [ i ] ;
 p = stpcpy ( p , "%m)" ) ;
 mpis [ nelem ++ ] = skey [ i ] ;
 }
 if ( extrainfo && ( algo == GCRY_PK_ECDSA || algo == GCRY_PK_ECDH ) ) {
 percent_s_idx = nelem ;
 p = stpcpy ( p , "%S" ) ;
 }
 p = stpcpy ( p , "))" ) ;
 p = stpcpy ( p , "(private-key(" ) ;
 p = stpcpy ( p , algo_name ) ;
 for ( i = 0 ;
 sec_elems [ i ] ;
 i ++ ) {
 * p ++ = '(' ;
 * p ++ = sec_elems [ i ] ;
 p = stpcpy ( p , "%m)" ) ;
 mpis [ nelem ++ ] = skey [ i ] ;
 }
 p = stpcpy ( p , "))" ) ;
 skey [ i ] = NULL ;
 if ( extrainfo && percent_s_idx == - 1 ) {
 p = stpcpy ( p , "%S" ) ;
 }
 else if ( factors && factors [ 0 ] ) {
 p = stpcpy ( p , "(misc-key-info(pm1-factors" ) ;
 for ( i = 0 ;
 factors [ i ] ;
 i ++ ) {
 p = stpcpy ( p , "%m" ) ;
 mpis [ nelem ++ ] = factors [ i ] ;
 }
 p = stpcpy ( p , "))" ) ;
 }
 strcpy ( p , ")" ) ;
 gcry_assert ( p - string < needed ) ;
 while ( nelem < DIM ( mpis ) ) mpis [ nelem ++ ] = NULL ;
 {
 int elem_n = strlen ( pub_elems ) + strlen ( sec_elems ) ;
 void * * arg_list ;
 arg_list = gcry_calloc ( nelem_cp + 1 , sizeof * arg_list ) ;
 if ( ! arg_list ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 for ( i = j = 0 ;
 i < elem_n ;
 i ++ ) {
 if ( i == percent_s_idx ) arg_list [ j ++ ] = & extrainfo ;
 arg_list [ j ++ ] = mpis + i ;
 }
 if ( extrainfo && percent_s_idx == - 1 ) arg_list [ j ] = & extrainfo ;
 else if ( factors && factors [ 0 ] ) {
 for ( ;
 i < nelem_cp ;
 i ++ ) arg_list [ j ++ ] = factors + i - elem_n ;
 }
 rc = gcry_sexp_build_array ( r_key , NULL , string , arg_list ) ;
 gcry_free ( arg_list ) ;
 if ( rc ) BUG ( ) ;
 gcry_assert ( DIM ( mpis ) == 30 ) ;
 }
 gcry_free ( string ) ;
 }
 leave : gcry_free ( name ) ;
 gcry_sexp_release ( extrainfo ) ;
 release_mpi_array ( skey ) ;
 if ( factors ) {
 release_mpi_array ( factors ) ;
 gcry_free ( factors ) ;
 }
 gcry_sexp_release ( l3 ) ;
 gcry_sexp_release ( l2 ) ;
 gcry_sexp_release ( list ) ;
 if ( module ) {
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 _gcry_module_release ( module ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }
 return gcry_error ( rc ) ;
 }