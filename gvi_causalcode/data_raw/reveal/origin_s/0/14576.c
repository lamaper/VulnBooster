ev_int64_t evutil_strtoll ( const char * s , char * * endptr , int base ) {



 if ( base != 10 ) return 0 ;
 r = ( ev_int64_t ) _atoi64 ( s ) ;
 while ( isspace ( * s ) ) ++ s ;
 while ( isdigit ( * s ) ) ++ s ;
 if ( endptr ) * endptr = ( char * ) s ;
 return r ;

