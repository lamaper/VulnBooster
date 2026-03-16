static void read_once_cb ( int fd , short event , void * arg ) {
 char buf [ 256 ] ;
 int len ;
 len = read ( fd , buf , sizeof ( buf ) ) ;
 if ( called ) {
 test_ok = 0 ;
 }
 else if ( len ) {
 write ( pair [ 0 ] , TEST1 , strlen ( TEST1 ) + 1 ) ;
 test_ok = 1 ;
 }
 called ++ ;
 }