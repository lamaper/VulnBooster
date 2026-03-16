static long get_millisecs_now ( void ) {

 gettimeofday ( & tv , NULL ) ;
 return ( tv . tv_sec ) * 1000L + ( tv . tv_usec ) / 1000 ;

 FILETIME ft ;
 __int64 * pi = ( __int64 * ) & ft ;
 GetLocalTime ( & st ) ;
 SystemTimeToFileTime ( & st , & ft ) ;
 return ( long ) ( ( * pi ) / 10000 ) ;
