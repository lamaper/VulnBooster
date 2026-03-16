static unsigned dummy_get_nbits ( int algorithm , gcry_mpi_t * pkey ) {
 ( void ) algorithm ;
 ( void ) pkey ;
 fips_signal_error ( "using dummy public key function" ) ;
 return 0 ;
 }