void TSCacheHttpInfoReqSet ( TSCacheHttpInfo infop , TSMBuffer bufp , TSMLoc obj ) {
 HTTPHdr h ;
 SET_HTTP_HDR ( h , bufp , obj ) ;
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 info -> request_set ( & h ) ;
 }