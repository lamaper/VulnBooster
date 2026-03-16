static void fifo_read ( int fd , short event , void * arg ) {
 char buf [ 255 ] ;
 int len ;
 struct event * ev = arg ;


 fprintf ( stderr , "fifo_read called with fd: %d, event: %d, arg: %p\n" , fd , event , arg ) ;

 if ( len && dwBytesRead == 0 ) {
 fprintf ( stderr , "End Of File" ) ;
 event_del ( ev ) ;
 return ;
 }
 buf [ dwBytesRead ] = '\0' ;

 if ( len == - 1 ) {
 perror ( "read" ) ;
 return ;
 }
 else if ( len == 0 ) {
 fprintf ( stderr , "Connection closed\n" ) ;
 return ;
 }
 buf [ len ] = '\0' ;

 }