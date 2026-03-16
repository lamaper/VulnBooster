CURLcode Curl_add_buffer ( Curl_send_buffer * in , const void * inptr , size_t size ) {
 char * new_rb ;
 size_t new_size ;
 if ( ~ size < in -> size_used ) {
 Curl_safefree ( in -> buffer ) ;
 free ( in ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 if ( ! in -> buffer || ( ( in -> size_used + size ) > ( in -> size_max - 1 ) ) ) {
 if ( ( size > ( size_t ) - 1 / 2 ) || ( in -> size_used > ( size_t ) - 1 / 2 ) || ( ~ ( size * 2 ) < ( in -> size_used * 2 ) ) ) new_size = ( size_t ) - 1 ;
 else new_size = ( in -> size_used + size ) * 2 ;
 if ( in -> buffer ) new_rb = realloc ( in -> buffer , new_size ) ;
 else new_rb = malloc ( new_size ) ;
 if ( ! new_rb ) {
 Curl_safefree ( in -> buffer ) ;
 free ( in ) ;
 return CURLE_OUT_OF_MEMORY ;
 }
 in -> buffer = new_rb ;
 in -> size_max = new_size ;
 }
 memcpy ( & in -> buffer [ in -> size_used ] , inptr , size ) ;
 in -> size_used += size ;
 return CURLE_OK ;
 }