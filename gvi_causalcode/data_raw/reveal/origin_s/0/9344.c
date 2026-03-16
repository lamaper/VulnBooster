static void start_move ( struct transfer_request * request ) {
 struct active_request_slot * slot ;
 struct curl_slist * dav_headers = NULL ;
 slot = get_active_slot ( ) ;
 slot -> callback_func = process_response ;
 slot -> callback_data = request ;
 curl_setup_http_get ( slot -> curl , request -> url , DAV_MOVE ) ;
 dav_headers = curl_slist_append ( dav_headers , request -> dest ) ;
 dav_headers = curl_slist_append ( dav_headers , "Overwrite: T" ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 if ( start_active_slot ( slot ) ) {
 request -> slot = slot ;
 request -> state = RUN_MOVE ;
 }
 else {
 request -> state = ABORTED ;
 free ( request -> url ) ;
 request -> url = NULL ;
 }
 }