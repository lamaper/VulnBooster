TSCacheHttpInfo TSCacheHttpInfoCreate ( void ) {
 CacheHTTPInfo * info = new CacheHTTPInfo ;
 info -> create ( ) ;
 return reinterpret_cast < TSCacheHttpInfo > ( info ) ;
 }