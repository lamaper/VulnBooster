static void print_mpi_2 ( const char * text , const char * text2 , gcry_mpi_t a ) {
 gcry_error_t err ;
 char * buf ;
 void * bufaddr = & buf ;
 err = gcry_mpi_aprint ( GCRYMPI_FMT_HEX , bufaddr , NULL , a ) ;
 if ( err ) fprintf ( stderr , "%s%s: [error printing number: %s]\n" , text , text2 ? text2 : "" , gpg_strerror ( err ) ) ;
 else {
 fprintf ( stderr , "%s%s: %s\n" , text , text2 ? text2 : "" , buf ) ;
 gcry_free ( buf ) ;
 }
 }