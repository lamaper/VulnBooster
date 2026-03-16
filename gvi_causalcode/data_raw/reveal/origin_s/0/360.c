static u16 default_transaction_id_fn ( void ) {
 u16 trans_id ;

 static int clkid = - 1 ;
 if ( clkid == - 1 ) {
 clkid = CLOCK_REALTIME ;


 if ( clock_gettime ( clkid , & ts ) == - 1 ) event_err ( 1 , "clock_gettime" ) ;
 trans_id = ts . tv_nsec & 0xffff ;

 _ftime ( & tb ) ;
 trans_id = tb . millitm & 0xffff ;

 evutil_gettimeofday ( & tv , NULL ) ;
 trans_id = tv . tv_usec & 0xffff ;

 abort ( ) ;
 }

 }