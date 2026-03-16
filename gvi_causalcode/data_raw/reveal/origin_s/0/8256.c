static void curl_setup_http ( CURL * curl , const char * url , const char * custom_req , struct buffer * buffer , curl_write_callback write_fn ) {
 curl_easy_setopt ( curl , CURLOPT_PUT , 1 ) ;
 curl_easy_setopt ( curl , CURLOPT_URL , url ) ;
 curl_easy_setopt ( curl , CURLOPT_INFILE , buffer ) ;
 curl_easy_setopt ( curl , CURLOPT_INFILESIZE , buffer -> buf . len ) ;
 curl_easy_setopt ( curl , CURLOPT_READFUNCTION , fread_buffer ) ;

 curl_easy_setopt ( curl , CURLOPT_IOCTLDATA , buffer ) ;

 curl_easy_setopt ( curl , CURLOPT_NOBODY , 0 ) ;
 curl_easy_setopt ( curl , CURLOPT_CUSTOMREQUEST , custom_req ) ;
 curl_easy_setopt ( curl , CURLOPT_UPLOAD , 1 ) ;
 }