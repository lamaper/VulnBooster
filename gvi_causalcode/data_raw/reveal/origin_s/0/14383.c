static void curl_setup_http_get ( CURL * curl , const char * url , const char * custom_req ) {
 curl_easy_setopt ( curl , CURLOPT_HTTPGET , 1 ) ;
 curl_easy_setopt ( curl , CURLOPT_URL , url ) ;
 curl_easy_setopt ( curl , CURLOPT_CUSTOMREQUEST , custom_req ) ;
 curl_easy_setopt ( curl , CURLOPT_WRITEFUNCTION , fwrite_null ) ;
 }