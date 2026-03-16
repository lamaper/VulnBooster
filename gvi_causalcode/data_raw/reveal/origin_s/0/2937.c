static int unlock_remote ( struct remote_lock * lock ) {
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct remote_lock * prev = repo -> locks ;
 struct curl_slist * dav_headers ;
 int rc = 0 ;
 dav_headers = get_dav_token_headers ( lock , DAV_HEADER_LOCK ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http_get ( slot -> curl , lock -> url , DAV_UNLOCK ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result == CURLE_OK ) rc = 1 ;
 else fprintf ( stderr , "UNLOCK HTTP error %ld\n" , results . http_code ) ;
 }
 else {
 fprintf ( stderr , "Unable to start UNLOCK request\n" ) ;
 }
 curl_slist_free_all ( dav_headers ) ;
 if ( repo -> locks == lock ) {
 repo -> locks = lock -> next ;
 }
 else {
 while ( prev && prev -> next != lock ) prev = prev -> next ;
 if ( prev ) prev -> next = prev -> next -> next ;
 }
 free ( lock -> owner ) ;
 free ( lock -> url ) ;
 free ( lock -> token ) ;
 free ( lock ) ;
 return rc ;
 }