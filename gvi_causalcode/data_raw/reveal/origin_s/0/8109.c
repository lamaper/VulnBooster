static int cleanup_test ( void ) {

 close ( pair [ 1 ] ) ;

 CloseHandle ( ( HANDLE ) pair [ 1 ] ) ;

 else {
 fprintf ( stdout , "FAILED\n" ) ;
 exit ( 1 ) ;
 }
 test_ok = 0 ;
 return ( 0 ) ;
 }