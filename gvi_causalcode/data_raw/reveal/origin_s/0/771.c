static int refresh_lock ( struct remote_lock * lock ) {
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct curl_slist * dav_headers ;
 int rc = 0 ;
 lock -> refreshing = 1 ;
 dav_headers = get_dav_token_headers ( lock , DAV_HEADER_IF | DAV_HEADER_TIMEOUT ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http_get ( slot -> curl , lock -> url , DAV_LOCK ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result != CURLE_OK ) {
 fprintf ( stderr , "LOCK HTTP error %ld\n" , results . http_code ) ;
 }
 else {
 lock -> start_time = time ( NULL ) ;
 rc = 1 ;
 }
 }
 lock -> refreshing = 0 ;
 curl_slist_free_all ( dav_headers ) ;
 return rc ;
 }