static void init_signal_handling ( void ) {
 struct sigaction sa ;
 DBUG_ENTER ( "init_signal_handling" ) ;


 sigemptyset ( & sa . sa_mask ) ;
 sigprocmask ( SIG_SETMASK , & sa . sa_mask , NULL ) ;
 sa . sa_handler = signal_handler ;
 sigaction ( SIGSEGV , & sa , NULL ) ;
 sigaction ( SIGABRT , & sa , NULL ) ;


 sigaction ( SIGFPE , & sa , NULL ) ;
 DBUG_VOID_RETURN ;
 }