CURLcode Curl_add_bufferf ( Curl_send_buffer * in , const char * fmt , ... ) {
 char * s ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 s = vaprintf ( fmt , ap ) ;
 va_end ( ap ) ;
 if ( s ) {
 CURLcode result = Curl_add_buffer ( in , s , strlen ( s ) ) ;
 free ( s ) ;
 return result ;
 }
 free ( in -> buffer ) ;
 free ( in ) ;
 return CURLE_OUT_OF_MEMORY ;
 }