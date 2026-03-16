int64 feGetCurrentTimestamp ( void ) {
 int64 result ;
 struct timeval tp ;
 gettimeofday ( & tp , NULL ) ;
 result = ( int64 ) tp . tv_sec - ( ( POSTGRES_EPOCH_JDATE - UNIX_EPOCH_JDATE ) * SECS_PER_DAY ) ;
 result = ( result * USECS_PER_SEC ) + tp . tv_usec ;
 return result ;
 }