static int update_remote ( unsigned char * sha1 , struct remote_lock * lock ) {
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct buffer out_buffer = {
 STRBUF_INIT , 0 }
 ;
 struct curl_slist * dav_headers ;
 dav_headers = get_dav_token_headers ( lock , DAV_HEADER_IF ) ;
 strbuf_addf ( & out_buffer . buf , "%s\n" , sha1_to_hex ( sha1 ) ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http ( slot -> curl , lock -> url , DAV_PUT , & out_buffer , fwrite_null ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 strbuf_release ( & out_buffer . buf ) ;
 if ( results . curl_result != CURLE_OK ) {
 fprintf ( stderr , "PUT error: curl result=%d, HTTP code=%ld\n" , results . curl_result , results . http_code ) ;
 return 0 ;
 }
 }
 else {
 strbuf_release ( & out_buffer . buf ) ;
 fprintf ( stderr , "Unable to start PUT request\n" ) ;
 return 0 ;
 }
 return 1 ;
 }