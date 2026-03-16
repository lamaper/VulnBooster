static CURLcode expect100 ( struct Curl_easy * data , struct connectdata * conn , Curl_send_buffer * req_buffer ) {
 CURLcode result = CURLE_OK ;
 const char * ptr ;
 data -> state . expect100header = FALSE ;
 if ( use_http_1_1plus ( data , conn ) && ( conn -> httpversion != 20 ) ) {
 ptr = Curl_checkheaders ( conn , "Expect:" ) ;
 if ( ptr ) {
 data -> state . expect100header = Curl_compareheader ( ptr , "Expect:" , "100-continue" ) ;
 }
 else {
 result = Curl_add_bufferf ( req_buffer , "Expect: 100-continue\r\n" ) ;
 if ( ! result ) data -> state . expect100header = TRUE ;
 }
 }
 return result ;
 }