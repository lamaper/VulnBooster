inline static bool is_negative_caching_appropriate ( HttpTransact : : State * s ) {
 if ( ! s -> txn_conf -> negative_caching_enabled || ! s -> hdr_info . server_response . valid ( ) ) {
 return false ;
 }
 switch ( s -> hdr_info . server_response . status_get ( ) ) {
 case HTTP_STATUS_NO_CONTENT : case HTTP_STATUS_USE_PROXY : case HTTP_STATUS_BAD_REQUEST : case HTTP_STATUS_FORBIDDEN : case HTTP_STATUS_NOT_FOUND : case HTTP_STATUS_METHOD_NOT_ALLOWED : case HTTP_STATUS_REQUEST_URI_TOO_LONG : case HTTP_STATUS_INTERNAL_SERVER_ERROR : case HTTP_STATUS_NOT_IMPLEMENTED : case HTTP_STATUS_BAD_GATEWAY : case HTTP_STATUS_SERVICE_UNAVAILABLE : case HTTP_STATUS_GATEWAY_TIMEOUT : return true ;
 default : break ;
 }
 return false ;
 }