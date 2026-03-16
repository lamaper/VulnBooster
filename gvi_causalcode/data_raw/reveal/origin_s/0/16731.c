static gcry_err_code_t dummy_decrypt ( int algorithm , gcry_mpi_t * result , gcry_mpi_t * data , gcry_mpi_t * skey , int flags ) {
 ( void ) algorithm ;
 ( void ) result ;
 ( void ) data ;
 ( void ) skey ;
 ( void ) flags ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }