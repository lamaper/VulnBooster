gcry_error_t gcry_pk_sign ( gcry_sexp_t * r_sig , gcry_sexp_t s_hash , gcry_sexp_t s_skey ) {
 gcry_mpi_t * skey = NULL , hash = NULL , * result = NULL ;
 gcry_pk_spec_t * pubkey = NULL ;
 gcry_module_t module = NULL ;
 const char * algo_name , * algo_elems ;
 struct pk_encoding_ctx ctx ;
 int i ;
 int is_ecc ;
 gcry_err_code_t rc ;
 * r_sig = NULL ;
 REGISTER_DEFAULT_PUBKEYS ;
 rc = sexp_to_key ( s_skey , 1 , GCRY_PK_USAGE_SIGN , NULL , & skey , & module , & is_ecc ) ;
 if ( rc ) goto leave ;
 gcry_assert ( module ) ;
 pubkey = ( gcry_pk_spec_t * ) module -> spec ;
 algo_name = pubkey -> aliases ? * pubkey -> aliases : NULL ;
 if ( ! algo_name || ! * algo_name ) algo_name = pubkey -> name ;
 algo_elems = pubkey -> elements_sig ;
 init_encoding_ctx ( & ctx , PUBKEY_OP_SIGN , is_ecc ? 0 : gcry_pk_get_nbits ( s_skey ) ) ;
 rc = sexp_data_to_mpi ( s_hash , & hash , & ctx ) ;
 if ( rc ) goto leave ;
 result = gcry_calloc ( strlen ( algo_elems ) + 1 , sizeof ( * result ) ) ;
 if ( ! result ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 rc = pubkey_sign ( module -> mod_id , result , hash , skey , & ctx ) ;
 if ( rc ) goto leave ;
 if ( ctx . encoding == PUBKEY_ENC_PSS || ctx . encoding == PUBKEY_ENC_PKCS1 ) {
 unsigned char * em ;
 size_t emlen = ( ctx . nbits + 7 ) / 8 ;
 rc = octet_string_from_mpi ( & em , NULL , result [ 0 ] , emlen ) ;
 if ( rc ) goto leave ;
 rc = gcry_err_code ( gcry_sexp_build ( r_sig , NULL , "(sig-val(%s(s%b)))" , algo_name , ( int ) emlen , em ) ) ;
 gcry_free ( em ) ;
 if ( rc ) goto leave ;
 }
 else {
 char * string , * p ;
 size_t nelem , needed = strlen ( algo_name ) + 20 ;
 void * * arg_list ;
 nelem = strlen ( algo_elems ) ;
 needed += 10 * nelem ;
 string = p = gcry_malloc ( needed ) ;
 if ( ! string ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 p = stpcpy ( p , "(sig-val(" ) ;
 p = stpcpy ( p , algo_name ) ;
 for ( i = 0 ;
 algo_elems [ i ] ;
 i ++ ) {
 * p ++ = '(' ;
 * p ++ = algo_elems [ i ] ;
 p = stpcpy ( p , "%M)" ) ;
 }
 strcpy ( p , "))" ) ;
 arg_list = malloc ( nelem * sizeof * arg_list ) ;
 if ( ! arg_list ) {
 rc = gpg_err_code_from_syserror ( ) ;
 goto leave ;
 }
 for ( i = 0 ;
 i < nelem ;
 i ++ ) arg_list [ i ] = result + i ;
 rc = gcry_sexp_build_array ( r_sig , NULL , string , arg_list ) ;
 free ( arg_list ) ;
 if ( rc ) BUG ( ) ;
 gcry_free ( string ) ;
 }
 leave : if ( skey ) {
 if ( is_ecc ) for ( i = 0 ;
 i < 7 ;
 i ++ ) {
 if ( skey [ i ] ) mpi_free ( skey [ i ] ) ;
 skey [ i ] = NULL ;
 }
 else release_mpi_array ( skey ) ;
 gcry_free ( skey ) ;
 }
 if ( hash ) mpi_free ( hash ) ;
 if ( result ) {
 release_mpi_array ( result ) ;
 gcry_free ( result ) ;
 }
 return gcry_error ( rc ) ;
 }