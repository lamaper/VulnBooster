static void internal_endent ( void ) {
 if ( stream != NULL ) {
 fclose ( stream ) ;
 stream = NULL ;
 }
 }