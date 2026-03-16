ngx_int_t passenger_content_handler ( ngx_http_request_t * r ) {
 ngx_int_t rc ;
 ngx_http_upstream_t * u ;
 passenger_loc_conf_t * slcf ;
 ngx_str_t path , base_uri ;
 u_char * path_last , * end ;
 u_char root_path_str [ NGX_MAX_PATH + 1 ] ;
 ngx_str_t root_path ;
 size_t root_len , len ;
 u_char page_cache_file_str [ NGX_MAX_PATH + 1 ] ;
 ngx_str_t page_cache_file ;
 passenger_context_t * context ;
 PP_Error error ;
 if ( passenger_main_conf . root_dir . len == 0 ) {
 return NGX_DECLINED ;
 }
 else if ( r -> subrequest_in_memory ) {
 ngx_log_error ( NGX_LOG_ALERT , r -> connection -> log , 0 , "ngx_http_passenger_module does not support " "subrequest in memory" ) ;
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 slcf = ngx_http_get_module_loc_conf ( r , ngx_http_passenger_module ) ;
 if ( ! slcf -> enabled ) {
 return NGX_DECLINED ;
 }
 path_last = ngx_http_map_uri_to_path ( r , & path , & root_len , 0 ) ;
 if ( path_last != NULL && file_exists ( path . data , 0 ) ) {
 return NGX_DECLINED ;
 }
 end = ngx_copy ( root_path_str , path . data , root_len ) ;
 * end = '\0' ;
 root_path . data = root_path_str ;
 root_path . len = root_len ;
 context = ngx_pcalloc ( r -> pool , sizeof ( passenger_context_t ) ) ;
 if ( context == NULL ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 ngx_http_set_ctx ( r , context , ngx_http_passenger_module ) ;
 if ( find_base_uri ( r , slcf , & base_uri ) ) {
 if ( slcf -> document_root . data != NULL ) {
 len = slcf -> document_root . len + 1 ;
 context -> public_dir . data = ngx_palloc ( r -> pool , sizeof ( u_char ) * len ) ;
 end = ngx_copy ( context -> public_dir . data , slcf -> document_root . data , slcf -> document_root . len ) ;
 }
 else {
 len = root_path . len + base_uri . len + 1 ;
 context -> public_dir . data = ngx_palloc ( r -> pool , sizeof ( u_char ) * len ) ;
 end = ngx_copy ( context -> public_dir . data , root_path . data , root_path . len ) ;
 end = ngx_copy ( end , base_uri . data , base_uri . len ) ;
 }
 * end = '\0' ;
 context -> public_dir . len = len - 1 ;
 context -> base_uri = base_uri ;
 }
 else {
 len = sizeof ( u_char * ) * ( root_path . len + 1 ) ;
 context -> public_dir . data = ngx_palloc ( r -> pool , len ) ;
 end = ngx_copy ( context -> public_dir . data , root_path . data , root_path . len ) ;
 * end = '\0' ;
 context -> public_dir . len = root_path . len ;
 }
 page_cache_file . data = page_cache_file_str ;
 page_cache_file . len = sizeof ( page_cache_file_str ) ;
 if ( map_uri_to_page_cache_file ( r , & context -> public_dir , path . data , path_last - path . data , & page_cache_file ) ) {
 return passenger_static_content_handler ( r , & page_cache_file ) ;
 }
 if ( slcf -> app_type . data == NULL ) {
 pp_error_init ( & error ) ;
 if ( slcf -> app_root . data == NULL ) {
 context -> app_type = pp_app_type_detector_check_document_root ( pp_app_type_detector , ( const char * ) context -> public_dir . data , context -> public_dir . len , context -> base_uri . len != 0 , & error ) ;
 }
 else {
 context -> app_type = pp_app_type_detector_check_app_root ( pp_app_type_detector , ( const char * ) slcf -> app_root . data , slcf -> app_root . len , & error ) ;
 }
 if ( context -> app_type == PAT_NONE ) {
 return NGX_DECLINED ;
 }
 else if ( context -> app_type == PAT_ERROR ) {
 if ( error . errnoCode == EACCES ) {
 ngx_log_error ( NGX_LOG_ALERT , r -> connection -> log , 0 , "%s;
 This error means that the Nginx worker process (PID %d, " "running as UID %d) does not have permission to access this file. " "Please read the manual to learn how to fix this problem: " "section 'Troubleshooting' -> 'Upon accessing the web app, Nginx " "reports a \"Permission denied\" error';
 Extra info" , error . message , ( int ) getpid ( ) , ( int ) getuid ( ) ) ;
 }
 else {
 ngx_log_error ( NGX_LOG_ALERT , r -> connection -> log , ( error . errnoCode == PP_NO_ERRNO ) ? 0 : error . errnoCode , "%s" , error . message ) ;
 }
 pp_error_destroy ( & error ) ;
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 }
 else {
 context -> app_type = pp_get_app_type2 ( ( const char * ) slcf -> app_type . data , slcf -> app_type . len ) ;
 if ( context -> app_type == PAT_NONE ) {
 return NGX_DECLINED ;
 }
 }
 if ( ngx_http_upstream_create ( r ) != NGX_OK ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 u = r -> upstream ;
 u -> schema = pp_schema_string ;
 u -> output . tag = ( ngx_buf_tag_t ) & ngx_http_passenger_module ;
 set_upstream_server_address ( u , & slcf -> upstream_config ) ;
 u -> conf = & slcf -> upstream_config ;


 u -> reinit_request = reinit_request ;
 u -> process_header = process_status_line ;
 u -> abort_request = abort_request ;
 u -> finalize_request = finalize_request ;
 r -> state = 0 ;
 u -> buffering = slcf -> upstream_config . buffering ;
 u -> pipe = ngx_pcalloc ( r -> pool , sizeof ( ngx_event_pipe_t ) ) ;
 if ( u -> pipe == NULL ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 u -> pipe -> input_filter = ngx_event_pipe_copy_input_filter ;
 u -> pipe -> input_ctx = r ;
 rc = ngx_http_read_client_request_body ( r , ngx_http_upstream_init ) ;
 fix_peer_address ( r ) ;
 if ( rc >= NGX_HTTP_SPECIAL_RESPONSE ) {
 return rc ;
 }
 return NGX_DONE ;
 }