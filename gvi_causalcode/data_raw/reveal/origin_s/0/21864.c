int evutil_gettimeofday ( struct timeval * tv , struct timezone * tz ) {
 struct _timeb tb ;
 if ( tv == NULL ) return - 1 ;
 _ftime ( & tb ) ;
 tv -> tv_sec = ( long ) tb . time ;
 tv -> tv_usec = ( ( int ) tb . millitm ) * 1000 ;
 return 0 ;
 }