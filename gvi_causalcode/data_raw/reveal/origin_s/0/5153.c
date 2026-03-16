CURLcode Curl_add_timecondition ( struct Curl_easy * data , Curl_send_buffer * req_buffer ) {
 const struct tm * tm ;
 char * buf = data -> state . buffer ;
 struct tm keeptime ;
 CURLcode result ;
 if ( data -> set . timecondition == CURL_TIMECOND_NONE ) return CURLE_OK ;
 result = Curl_gmtime ( data -> set . timevalue , & keeptime ) ;
 if ( result ) {
 failf ( data , "Invalid TIMEVALUE" ) ;
 return result ;
 }
 tm = & keeptime ;
 snprintf ( buf , BUFSIZE - 1 , "%s, %02d %s %4d %02d:%02d:%02d GMT" , Curl_wkday [ tm -> tm_wday ? tm -> tm_wday - 1 : 6 ] , tm -> tm_mday , Curl_month [ tm -> tm_mon ] , tm -> tm_year + 1900 , tm -> tm_hour , tm -> tm_min , tm -> tm_sec ) ;
 switch ( data -> set . timecondition ) {
 default : break ;
 case CURL_TIMECOND_IFMODSINCE : result = Curl_add_bufferf ( req_buffer , "If-Modified-Since: %s\r\n" , buf ) ;
 break ;
 case CURL_TIMECOND_IFUNMODSINCE : result = Curl_add_bufferf ( req_buffer , "If-Unmodified-Since: %s\r\n" , buf ) ;
 break ;
 case CURL_TIMECOND_LASTMOD : result = Curl_add_bufferf ( req_buffer , "Last-Modified: %s\r\n" , buf ) ;
 break ;
 }
 return result ;
 }