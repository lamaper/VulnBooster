static void get_current_time ( struct timeval * t ) {

 union {
 unsigned __int64 ul ;
 FILETIME ft ;
 }
 now ;
 GetSystemTime ( & st ) ;
 SystemTimeToFileTime ( & st , & now . ft ) ;



 t -> tv_usec = ( ( int ) ( now . ul % 10000000 ) ) / 10 ;

 ftime ( & tb ) ;
 t -> tv_sec = ( long ) tb . time ;
 t -> tv_usec = ( long ) tb . millitm * 1000 ;

