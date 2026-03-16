static CURLcode http_perhapsrewind ( struct connectdata * conn ) {
 struct Curl_easy * data = conn -> data ;
 struct HTTP * http = data -> req . protop ;
 curl_off_t bytessent ;
 curl_off_t expectsend = - 1 ;
 if ( ! http ) return CURLE_OK ;
 switch ( data -> set . httpreq ) {
 case HTTPREQ_GET : case HTTPREQ_HEAD : return CURLE_OK ;
 default : break ;
 }
 bytessent = http -> writebytecount ;
 if ( conn -> bits . authneg ) {
 expectsend = 0 ;
 }
 else if ( ! conn -> bits . protoconnstart ) {
 expectsend = 0 ;
 }
 else {
 switch ( data -> set . httpreq ) {
 case HTTPREQ_POST : if ( data -> state . infilesize != - 1 ) expectsend = data -> state . infilesize ;
 else if ( data -> set . postfields ) expectsend = ( curl_off_t ) strlen ( data -> set . postfields ) ;
 break ;
 case HTTPREQ_PUT : if ( data -> state . infilesize != - 1 ) expectsend = data -> state . infilesize ;
 break ;
 case HTTPREQ_POST_FORM : expectsend = http -> postsize ;
 break ;
 default : break ;
 }
 }
 conn -> bits . rewindaftersend = FALSE ;
 if ( ( expectsend == - 1 ) || ( expectsend > bytessent ) ) {

 if ( ( ( expectsend - bytessent ) < 2000 ) || ( conn -> ntlm . state != NTLMSTATE_NONE ) || ( conn -> proxyntlm . state != NTLMSTATE_NONE ) ) {
 if ( ! conn -> bits . authneg ) {
 conn -> bits . rewindaftersend = TRUE ;
 infof ( data , "Rewind stream after send\n" ) ;
 }
 return CURLE_OK ;
 }
 if ( conn -> bits . close ) return CURLE_OK ;
 infof ( data , "NTLM send, close instead of sending %" CURL_FORMAT_CURL_OFF_T " bytes\n" , ( curl_off_t ) ( expectsend - bytessent ) ) ;
 }

 data -> req . size = 0 ;
 }
 if ( bytessent ) return Curl_readrewind ( conn ) ;
 return CURLE_OK ;
 }