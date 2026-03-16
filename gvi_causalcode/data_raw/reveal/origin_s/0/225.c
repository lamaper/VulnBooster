static void CheckMakeB ( BasePoint * test , BasePoint * good ) {
 if ( ! isfinite ( test -> x ) || test -> x > 100000 || test -> x < - 100000 ) {
 LogError ( _ ( "Value out of bounds in spline.\n" ) ) ;
 if ( good != NULL ) test -> x = good -> x ;
 else test -> x = 0 ;
 }
 if ( ! isfinite ( test -> y ) || test -> y > 100000 || test -> y < - 100000 ) {
 LogError ( _ ( "Value out of bounds in spline.\n" ) ) ;
 if ( good != NULL ) test -> y = good -> y ;
 else test -> y = 0 ;
 }
 }