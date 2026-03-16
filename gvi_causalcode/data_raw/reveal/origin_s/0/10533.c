static struct remote_lock * lock_remote ( const char * path , long timeout ) {
 struct active_request_slot * slot ;
 struct slot_results results ;
 struct buffer out_buffer = {
 STRBUF_INIT , 0 }
 ;
 struct strbuf in_buffer = STRBUF_INIT ;
 char * url ;
 char * ep ;
 char timeout_header [ 25 ] ;
 struct remote_lock * lock = NULL ;
 struct curl_slist * dav_headers = NULL ;
 struct xml_ctx ctx ;
 char * escaped ;
 url = xstrfmt ( "%s%s" , repo -> url , path ) ;
 ep = strchr ( url + strlen ( repo -> url ) + 1 , '/' ) ;
 while ( ep ) {
 char saved_character = ep [ 1 ] ;
 ep [ 1 ] = '\0' ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http_get ( slot -> curl , url , DAV_MKCOL ) ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result != CURLE_OK && results . http_code != 405 ) {
 fprintf ( stderr , "Unable to create branch path %s\n" , url ) ;
 free ( url ) ;
 return NULL ;
 }
 }
 else {
 fprintf ( stderr , "Unable to start MKCOL request\n" ) ;
 free ( url ) ;
 return NULL ;
 }
 ep [ 1 ] = saved_character ;
 ep = strchr ( ep + 1 , '/' ) ;
 }
 escaped = xml_entities ( ident_default_email ( ) ) ;
 strbuf_addf ( & out_buffer . buf , LOCK_REQUEST , escaped ) ;
 free ( escaped ) ;
 xsnprintf ( timeout_header , sizeof ( timeout_header ) , "Timeout: Second-%ld" , timeout ) ;
 dav_headers = curl_slist_append ( dav_headers , timeout_header ) ;
 dav_headers = curl_slist_append ( dav_headers , "Content-Type: text/xml" ) ;
 slot = get_active_slot ( ) ;
 slot -> results = & results ;
 curl_setup_http ( slot -> curl , url , DAV_LOCK , & out_buffer , fwrite_buffer ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_HTTPHEADER , dav_headers ) ;
 curl_easy_setopt ( slot -> curl , CURLOPT_FILE , & in_buffer ) ;
 lock = xcalloc ( 1 , sizeof ( * lock ) ) ;
 lock -> timeout = - 1 ;
 if ( start_active_slot ( slot ) ) {
 run_active_slot ( slot ) ;
 if ( results . curl_result == CURLE_OK ) {
 XML_Parser parser = XML_ParserCreate ( NULL ) ;
 enum XML_Status result ;
 ctx . name = xcalloc ( 10 , 1 ) ;
 ctx . len = 0 ;
 ctx . cdata = NULL ;
 ctx . userFunc = handle_new_lock_ctx ;
 ctx . userData = lock ;
 XML_SetUserData ( parser , & ctx ) ;
 XML_SetElementHandler ( parser , xml_start_tag , xml_end_tag ) ;
 XML_SetCharacterDataHandler ( parser , xml_cdata ) ;
 result = XML_Parse ( parser , in_buffer . buf , in_buffer . len , 1 ) ;
 free ( ctx . name ) ;
 if ( result != XML_STATUS_OK ) {
 fprintf ( stderr , "XML error: %s\n" , XML_ErrorString ( XML_GetErrorCode ( parser ) ) ) ;
 lock -> timeout = - 1 ;
 }
 XML_ParserFree ( parser ) ;
 }
 }
 else {
 fprintf ( stderr , "Unable to start LOCK request\n" ) ;
 }
 curl_slist_free_all ( dav_headers ) ;
 strbuf_release ( & out_buffer . buf ) ;
 strbuf_release ( & in_buffer ) ;
 if ( lock -> token == NULL || lock -> timeout <= 0 ) {
 free ( lock -> token ) ;
 free ( lock -> owner ) ;
 free ( url ) ;
 free ( lock ) ;
 lock = NULL ;
 }
 else {
 lock -> url = url ;
 lock -> start_time = time ( NULL ) ;
 lock -> next = repo -> locks ;
 repo -> locks = lock ;
 }
 return lock ;
 }