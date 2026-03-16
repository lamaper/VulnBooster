static void remove_locks_on_signal ( int signo ) {
 remove_locks ( ) ;
 sigchain_pop ( signo ) ;
 raise ( signo ) ;
 }