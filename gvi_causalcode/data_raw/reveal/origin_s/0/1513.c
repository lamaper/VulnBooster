bool feTimestampDifferenceExceeds ( int64 start_time , int64 stop_time , int msec ) {
 int64 diff = stop_time - start_time ;
 return ( diff >= msec * INT64CONST ( 1000 ) ) ;
 }