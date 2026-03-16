bool Curl_compareheader ( const char * headerline , const char * header , const char * content ) {
 size_t hlen = strlen ( header ) ;
 size_t clen ;
 size_t len ;
 const char * start ;
 const char * end ;
 if ( ! Curl_raw_nequal ( headerline , header , hlen ) ) return FALSE ;
 start = & headerline [ hlen ] ;
 while ( * start && ISSPACE ( * start ) ) start ++ ;
 end = strchr ( start , '\r' ) ;
 if ( ! end ) {
 end = strchr ( start , '\n' ) ;
 if ( ! end ) end = strchr ( start , '\0' ) ;
 }
 len = end - start ;
 clen = strlen ( content ) ;
 for ( ;
 len >= clen ;
 len -- , start ++ ) {
 if ( Curl_raw_nequal ( start , content , clen ) ) return TRUE ;
 }
 return FALSE ;
 }