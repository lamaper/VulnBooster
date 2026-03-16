static gcry_mpi_t hex2mpi ( const char * string ) {
 gpg_error_t err ;
 gcry_mpi_t val ;
 err = gcry_mpi_scan ( & val , GCRYMPI_FMT_HEX , string , 0 , NULL ) ;
 if ( err ) die ( "hex2mpi '%s' failed: %s\n" , gpg_strerror ( err ) ) ;
 return val ;
 }