static int locking_available ( void ) {
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct strbuf in_buffer = STRBUF_INIT ;
 struct buffer out_buffer = {
 STRBUF_INIT , 0 }
 ;
 struct curl_slist * dav_headers = NULL ;
 struct xml_ctx ctx ;
 int lock_flags = 0 ;
 char * escaped ;
 escaped = xml_entities ( repo -> url ) ;
 strbuf_addf ( & out_buffer . buf , PROPFIND_SUPPORTEDLOCK_REQUEST , escaped ) ;
 free ( escaped ) ;
 dav_headers = curl_slist_append ( dav_headers , "Depth: 0" ) ;
 dav_headers = curl_slist_append ( dav_headers , "Content-Type: text/xml" ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http ( slot -> curl , repo -> url , DAV_PROPFIND , & out_buffer , fwrite_buffer ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_FILE , & in_buffer ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result == CURLE_OK ) {
 XML_Parser parser = XML_ParserCreate ( NULL ) ;
 enum XML_Status result ;
 ctx . name = xcalloc ( 10 , 1 ) ;
 ctx . len = 0 ;
 ctx . cdata = NULL ;
 ctx . userFunc = handle_lockprop_ctx ;
 ctx . userData = & lock_flags ;
 XML_SetUserData ( parser , & ctx ) ;
 XML_SetElementHandler ( parser , xml_start_tag , xml_end_tag ) ;
 result = XML_Parse ( parser , in_buffer . buf , in_buffer . len , 1 ) ;
 free ( ctx . name ) ;
 if ( result != XML_STATUS_OK ) {
 fprintf ( stderr , "XML error: %s\n" , XML_ErrorString ( XML_GetErrorCode ( parser ) ) ) ;
 lock_flags = 0 ;
 }
 XML_ParserFree ( parser ) ;
 if ( ! lock_flags ) error ( "no DAV locking support on %s" , repo -> url ) ;
 }
 else {
 error ( "Cannot access URL %s, return code %d" , repo -> url , results . curl_result ) ;
 lock_flags = 0 ;
 }
 }
 else {
 error ( "Unable to start PROPFIND request on %s" , repo -> url ) ;
 }
 strbuf_release ( & out_buffer . buf ) ;
 strbuf_release ( & in_buffer ) ;
 curl_slist_free_all ( dav_headers ) ;
 return lock_flags ;
 }