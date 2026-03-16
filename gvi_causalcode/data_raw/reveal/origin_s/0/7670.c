static void evtag_test ( void ) {
 fprintf ( stdout , "Testing Tagging:\n" ) ;
 evtag_init ( ) ;
 evtag_int_test ( ) ;
 evtag_fuzz ( ) ;
 evtag_tag_encoding ( ) ;
 fprintf ( stdout , "OK\n" ) ;
 }