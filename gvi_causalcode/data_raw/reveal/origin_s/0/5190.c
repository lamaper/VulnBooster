static void combined_write_cb ( int fd , short event , void * arg ) {
 struct both * both = arg ;
 char buf [ 128 ] ;
 int len ;
 len = sizeof ( buf ) ;
 if ( len > both -> nread ) len = both -> nread ;
 len = write ( fd , buf , len ) ;
 if ( len == - 1 ) fprintf ( stderr , "%s: write\n" , __func__ ) ;
 if ( len <= 0 ) {
 shutdown ( fd , SHUT_WR ) ;
 return ;
 }
 both -> nread -= len ;
 if ( event_add ( & both -> ev , NULL ) == - 1 ) exit ( 1 ) ;
 }