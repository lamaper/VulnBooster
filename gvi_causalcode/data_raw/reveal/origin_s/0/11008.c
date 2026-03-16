void check_time_sanity ( int * e ) {
 if ( start_time == ( time_t ) 0 ) error [ ( * e ) ++ ] . message = strdup ( "Start time can't be zero or date format couldn't be recognized correctly" ) ;
 if ( end_time == ( time_t ) 0 ) error [ ( * e ) ++ ] . message = strdup ( "End time can't be zero or date format couldn't be recognized correctly" ) ;
 if ( end_time < start_time ) error [ ( * e ) ++ ] . message = strdup ( "End date before start date" ) ;
 return ;
 }