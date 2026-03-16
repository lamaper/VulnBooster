static void update_remote_info_refs ( struct remote_lock * lock ) {
 struct buffer buffer = {
 STRBUF_INIT , 0 }
 ;
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct curl_slist * dav_headers ;
 remote_ls ( "refs/" , ( PROCESS_FILES | RECURSIVE ) , add_remote_info_ref , & buffer . buf ) ;
 if ( ! aborted ) {
 dav_headers = get_dav_token_headers ( lock , DAV_HEADER_IF ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http ( slot -> curl , lock -> url , DAV_PUT , & buffer , fwrite_null ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result != CURLE_OK ) {
 fprintf ( stderr , "PUT error: curl result=%d, HTTP code=%ld\n" , results . curl_result , results . http_code ) ;
 }
 }
 }
 strbuf_release ( & buffer . buf ) ;
 }