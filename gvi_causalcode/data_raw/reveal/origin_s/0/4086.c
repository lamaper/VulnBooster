static void remote_ls ( const char * path , int flags , void ( * userFunc ) ( struct remote_ls_ctx * ls ) , void * userData ) {
 char * url = xstrfmt ( "%s%s" , repo -> url , path ) ;
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct strbuf in_buffer = STRBUF_INIT ;
 struct buffer out_buffer = {
 STRBUF_INIT , 0 }
 ;
 struct curl_slist * dav_headers = NULL ;
 struct xml_ctx ctx ;
 struct remote_ls_ctx ls ;
 ls . flags = flags ;
 ls . path = xstrdup ( path ) ;
 ls . dentry_name = NULL ;
 ls . dentry_flags = 0 ;
 ls . userData = userData ;
 ls . userFunc = userFunc ;
 strbuf_addf ( & out_buffer . buf , PROPFIND_ALL_REQUEST ) ;
 dav_headers = curl_slist_append ( dav_headers , "Depth: 1" ) ;
 dav_headers = curl_slist_append ( dav_headers , "Content-Type: text/xml" ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http ( slot -> curl , url , DAV_PROPFIND , & out_buffer , fwrite_buffer ) ;
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
 ctx . userFunc = handle_remote_ls_ctx ;
 ctx . userData = & ls ;
 XML_SetUserData ( parser , & ctx ) ;
 XML_SetElementHandler ( parser , xml_start_tag , xml_end_tag ) ;
 XML_SetCharacterDataHandler ( parser , xml_cdata ) ;
 result = XML_Parse ( parser , in_buffer . buf , in_buffer . len , 1 ) ;
 free ( ctx . name ) ;
 if ( result != XML_STATUS_OK ) {
 fprintf ( stderr , "XML error: %s\n" , XML_ErrorString ( XML_GetErrorCode ( parser ) ) ) ;
 }
 XML_ParserFree ( parser ) ;
 }
 }
 else {
 fprintf ( stderr , "Unable to start PROPFIND request\n" ) ;
 }
 free ( ls . path ) ;
 free ( url ) ;
 strbuf_release ( & out_buffer . buf ) ;
 strbuf_release ( & in_buffer ) ;
 curl_slist_free_all ( dav_headers ) ;
 }