static gcry_err_code_t dummy_encrypt ( int algorithm , gcry_mpi_t * resarr , gcry_mpi_t data , gcry_mpi_t * pkey , int flags ) {
 ( void ) algorithm ;
 ( void ) resarr ;
 ( void ) data ;
 ( void ) pkey ;
 ( void ) flags ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }