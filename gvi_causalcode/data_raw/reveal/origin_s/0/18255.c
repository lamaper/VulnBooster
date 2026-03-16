static gcry_err_code_t dummy_sign ( int algorithm , gcry_mpi_t * resarr , gcry_mpi_t data , gcry_mpi_t * skey , int flags , int hashalgo ) {
 ( void ) algorithm ;
 ( void ) resarr ;
 ( void ) data ;
 ( void ) skey ;
 ( void ) flags ;
 ( void ) hashalgo ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }