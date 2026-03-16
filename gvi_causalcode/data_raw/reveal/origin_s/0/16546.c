char * Curl_memdup ( const char * src , size_t length ) {
 char * buffer = malloc ( length ) ;
 if ( ! buffer ) return NULL ;
 memcpy ( buffer , src , length ) ;
 return buffer ;
 }