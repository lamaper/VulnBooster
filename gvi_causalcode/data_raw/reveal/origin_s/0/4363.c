static gcry_err_code_t dummy_check_secret_key ( int algorithm , gcry_mpi_t * skey ) {
 ( void ) algorithm ;
 ( void ) skey ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }