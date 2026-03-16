static void srec_init ( void ) {
 static bfd_boolean inited = FALSE ;
 if ( ! inited ) {
 inited = TRUE ;
 hex_init ( ) ;
 }
 }