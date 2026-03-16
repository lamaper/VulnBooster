void feTimestampDifference ( int64 start_time , int64 stop_time , long * secs , int * microsecs ) {
 int64 diff = stop_time - start_time ;
 if ( diff <= 0 ) {
 * secs = 0 ;
 * microsecs = 0 ;
 }
 else {
 * secs = ( long ) ( diff / USECS_PER_SEC ) ;
 * microsecs = ( int ) ( diff % USECS_PER_SEC ) ;
 }
 }