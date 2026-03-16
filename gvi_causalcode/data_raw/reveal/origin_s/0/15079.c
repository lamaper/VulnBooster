static int my_kill ( int pid , int sig ) {

 if ( ( proc = OpenProcess ( SYNCHRONIZE | PROCESS_TERMINATE , FALSE , pid ) ) == NULL ) return - 1 ;
 if ( sig == 0 ) {
 DWORD wait_result = WaitForSingleObject ( proc , 0 ) ;
 CloseHandle ( proc ) ;
 return wait_result == WAIT_OBJECT_0 ? - 1 : 0 ;
 }
 ( void ) TerminateProcess ( proc , 201 ) ;
 CloseHandle ( proc ) ;
 return 1 ;

