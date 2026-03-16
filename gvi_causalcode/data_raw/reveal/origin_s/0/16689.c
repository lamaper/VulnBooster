static void multiple_read_cb ( int fd , short event , void * arg ) {
 struct event * ev = arg ;
 int len ;
 len = read ( fd , rbuf + roff , sizeof ( rbuf ) - roff ) ;
 if ( len == - 1 ) fprintf ( stderr , "%s: read\n" , __func__ ) ;
 if ( len <= 0 ) {
 if ( usepersist ) event_del ( ev ) ;
 return ;
 }
 roff += len ;
 if ( ! usepersist ) {
 if ( event_add ( ev , NULL ) == - 1 ) exit ( 1 ) ;
 }
 }