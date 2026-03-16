static void simple_write_cb ( int fd , short event , void * arg ) {
 int len ;
 if ( arg == NULL ) return ;
 len = write ( fd , TEST1 , strlen ( TEST1 ) + 1 ) ;
 if ( len == - 1 ) test_ok = 0 ;
 else test_ok = 1 ;
 }