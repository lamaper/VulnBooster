static void combined_read_cb ( int fd , short event , void * arg ) {
 struct both * both = arg ;
 char buf [ 128 ] ;
 int len ;
 len = read ( fd , buf , sizeof ( buf ) ) ;
 if ( len == - 1 ) fprintf ( stderr , "%s: read\n" , __func__ ) ;
 if ( len <= 0 ) return ;
 both -> nread += len ;
 if ( event_add ( & both -> ev , NULL ) == - 1 ) exit ( 1 ) ;
 }