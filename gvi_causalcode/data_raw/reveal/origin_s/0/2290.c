gcry_error_t gcry_pk_testkey ( gcry_sexp_t s_key ) {
 gcry_module_t module = NULL ;
 gcry_mpi_t * key = NULL ;
 gcry_err_code_t rc ;
 REGISTER_DEFAULT_PUBKEYS ;
 rc = sexp_to_key ( s_key , 1 , 0 , NULL , & key , & module , NULL ) ;
 if ( ! rc ) {
 rc = pubkey_check_secret_key ( module -> mod_id , key ) ;
 release_mpi_array ( key ) ;
 gcry_free ( key ) ;
 }
 return gcry_error ( rc ) ;
 }