const char * evutil_getenv ( const char * varname ) {
 if ( evutil_issetugid ( ) ) return NULL ;
 return getenv ( varname ) ;
 }