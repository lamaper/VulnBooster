int TSCacheHttpInfoVector ( TSCacheHttpInfo infop , void * data , int length ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 CacheHTTPInfoVector vector ;
 vector . insert ( info ) ;
 int size = vector . marshal_length ( ) ;
 if ( size > length ) {
 return 0 ;
 }
 return vector . marshal ( ( char * ) data , length ) ;
 }