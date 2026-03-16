static void simple_read_cb ( int fd , short event , void * arg ) {
 char buf [ 256 ] ;
 int len ;
 if ( arg == NULL ) return ;
 len = read ( fd , buf , sizeof ( buf ) ) ;
 if ( len ) {
 if ( ! called ) {
 if ( event_add ( arg , NULL ) == - 1 ) exit ( 1 ) ;
 }
 }
 else if ( called == 1 ) test_ok = 1 ;
 called ++ ;
 }