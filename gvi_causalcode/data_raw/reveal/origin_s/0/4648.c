gcry_error_t gcry_pk_encrypt ( gcry_sexp_t * r_ciph , gcry_sexp_t s_data , gcry_sexp_t s_pkey ) {
 gcry_mpi_t * pkey = NULL , data = NULL , * ciph = NULL ;
 const char * algo_name , * algo_elems ;
 struct pk_encoding_ctx ctx ;
 gcry_err_code_t rc ;
 gcry_pk_spec_t * pubkey = NULL ;
 gcry_module_t module = NULL ;
 * r_ciph = NULL ;
 REGISTER_DEFAULT_PUBKEYS ;
 rc = sexp_to_key ( s_pkey , 0 , GCRY_PK_USAGE_ENCR , NULL , & pkey , & module , NULL ) ;
 if ( rc ) goto leave ;
 gcry_assert ( module ) ;
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 algo_name = pubkey -> aliases ? * pubkey -> aliases : NULL ;
 if ( ! algo_name || ! * algo_name ) algo_name = pubkey -> name ;
 algo_elems = pubkey -> elements_enc ;
 init_encoding_ctx ( & ctx , PUBKEY_OP_ENCRYPT , gcry_pk_get_nbits ( s_pkey ) ) ;
 rc = sexp_data_to_mpi ( s_data , & data , & ctx ) ;
 if ( rc ) goto leave ;
 ciph = gcry_calloc ( strlen ( algo_elems ) + 1 , sizeof ( * ciph ) ) ;
 if ( ! ciph ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 rc = pubkey_encrypt ( module -> mod_id , ciph , data , pkey , ctx . flags ) ;
 mpi_free ( data ) ;
 data = NULL ;
 if ( rc ) goto leave ;
 if ( ctx . encoding == PUBKEY_ENC_OAEP || ctx . encoding == PUBKEY_ENC_PKCS1 ) {
 unsigned char * em ;
 size_t emlen = ( ctx . nbits + 7 ) / 8 ;
 rc = octet_string_from_mpi ( & em , NULL , ciph [ 0 ] , emlen ) ;
 if ( rc ) goto leave ;
 rc = gcry_err_code ( gcry_sexp_build ( r_ciph , NULL , "(enc-val(%s(a%b)))" , algo_name , ( int ) emlen , em ) ) ;
 gcry_free ( em ) ;
 if ( rc ) goto leave ;
 }
 else {
 char * string , * p ;
 int i ;
 size_t nelem = strlen ( algo_elems ) ;
 size_t needed = 19 + strlen ( algo_name ) + ( nelem * 5 ) ;
 void * * arg_list ;
 string = p = gcry_malloc ( needed ) ;
 if ( ! string ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 p = stpcpy ( p , "(enc-val(" ) ;
 p = stpcpy ( p , algo_name ) ;
 for ( i = 0 ;
 algo_elems [ i ] ;
 i ++ ) {
 * p ++ = '(' ;
 * p ++ = algo_elems [ i ] ;
 p = stpcpy ( p , "%m)" ) ;
 }
 strcpy ( p , "))" ) ;
 arg_list = malloc ( nelem * sizeof * arg_list ) ;
 if ( ! arg_list ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 for ( i = 0 ;
 i < nelem ;
 i ++ ) arg_list [ i ] = ciph + i ;
 rc = gcry_sexp_build_array ( r_ciph , NULL , string , arg_list ) ;
 free ( arg_list ) ;
 if ( rc ) BUG ( ) ;
 gcry_free ( string ) ;
 }
 leave : if ( pkey ) {
 release_mpi_array ( pkey ) ;
 gcry_free ( pkey ) ;
 }
 if ( ciph ) {
 release_mpi_array ( ciph ) ;
 gcry_free ( ciph ) ;
 }
 if ( module ) {
 ath_mutex_lock ( & pubkeys_registered_lock ) ;
 _gcry_module_release ( module ) ;
 ath_mutex_unlock ( & pubkeys_registered_lock ) ;
 }
 gcry_free ( ctx . label ) ;
 return gcry_error ( rc ) ;
 }