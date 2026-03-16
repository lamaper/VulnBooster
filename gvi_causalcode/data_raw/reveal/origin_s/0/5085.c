static void * read_into_buffer ( FILE * fp , size_t * r_length ) {
 char * buffer ;
 size_t buflen ;
 size_t nread , bufsize = 0 ;
 * r_length = 0 ;


 buflen = 0 ;
 do {
 bufsize += NCHUNK ;
 buffer = realloc ( buffer , bufsize ) ;
 if ( ! buffer ) {
 perror ( "realloc failed" ) ;
 exit ( 1 ) ;
 }
 nread = fread ( buffer + buflen , 1 , NCHUNK , fp ) ;
 if ( nread < NCHUNK && ferror ( fp ) ) {
 perror ( "fread failed" ) ;
 exit ( 1 ) ;
 }
 buflen += nread ;
 }
 while ( nread == NCHUNK ) ;

 return buffer ;
 }