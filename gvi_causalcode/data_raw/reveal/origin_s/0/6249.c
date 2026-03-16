void TSCacheHttpInfoKeySet ( TSCacheHttpInfo infop , TSCacheKey keyp ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 INK_MD5 * key = ( INK_MD5 * ) keyp ;
 info -> object_key_set ( * key ) ;
 }