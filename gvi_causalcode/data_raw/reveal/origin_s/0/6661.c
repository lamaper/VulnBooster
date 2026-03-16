char * Curl_copy_header_value ( const char * header ) {
 const char * start ;
 const char * end ;
 char * value ;
 size_t len ;
 DEBUGASSERT ( header ) ;
 while ( * header && ( * header != ':' ) ) ++ header ;
 if ( * header ) ++ header ;
 start = header ;
 while ( * start && ISSPACE ( * start ) ) start ++ ;
 end = strchr ( start , '\r' ) ;
 if ( ! end ) end = strchr ( start , '\n' ) ;
 if ( ! end ) end = strchr ( start , '\0' ) ;
 if ( ! end ) return NULL ;
 while ( ( end > start ) && ISSPACE ( * end ) ) end -- ;
 len = end - start + 1 ;
 value = malloc ( len + 1 ) ;
 if ( ! value ) return NULL ;
 memcpy ( value , start , len ) ;
 value [ len ] = 0 ;
 return value ;
 }