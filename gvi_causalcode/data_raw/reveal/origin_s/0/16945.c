static void signal_cb_swp ( int sig , short event , void * arg ) {
 called ++ ;
 if ( called < 5 ) raise ( sig ) ;
 else event_loopexit ( NULL ) ;
 }