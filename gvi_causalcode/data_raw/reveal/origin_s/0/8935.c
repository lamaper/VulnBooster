static void termsig_handler ( int signum ) {
 atomic_cmpxchg ( & state , RUNNING , TERMINATE ) ;
 qemu_notify_event ( ) ;
 }