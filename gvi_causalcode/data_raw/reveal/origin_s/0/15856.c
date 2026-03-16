static void multiple_write_cb ( int fd , short event , void * arg ) {
 struct event * ev = arg ;
 int len ;
 len = 128 ;
 if ( woff + len >= sizeof ( wbuf ) ) len = sizeof ( wbuf ) - woff ;
 len = write ( fd , wbuf + woff , len ) ;
 if ( len == - 1 ) {
 fprintf ( stderr , "%s: write\n" , __func__ ) ;
 if ( usepersist ) event_del ( ev ) ;
 return ;
 }
 woff += len ;
 if ( woff >= sizeof ( wbuf ) ) {
 shutdown ( fd , SHUT_WR ) ;
 if ( usepersist ) event_del ( ev ) ;
 return ;
 }
 if ( ! usepersist ) {
 if ( event_add ( ev , NULL ) == - 1 ) exit ( 1 ) ;
 }
 }