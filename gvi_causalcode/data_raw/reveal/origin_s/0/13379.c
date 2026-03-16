static gcry_err_code_t dummy_generate ( int algorithm , unsigned int nbits , unsigned long dummy , gcry_mpi_t * skey , gcry_mpi_t * * retfactors ) {
 ( void ) algorithm ;
 ( void ) nbits ;
 ( void ) dummy ;
 ( void ) skey ;
 ( void ) retfactors ;
 fips_signal_error ( "using dummy public key function" ) ;
 return GPG_ERR_NOT_IMPLEMENTED ;
 }