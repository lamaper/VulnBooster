static ngx_int_t create_request ( ngx_http_request_t * r ) {
 u_char ch ;
 const char * helper_agent_request_socket_password_data ;
 unsigned int helper_agent_request_socket_password_len ;
 u_char buf [ sizeof ( "4294967296" ) + 1 ] ;
 size_t len , size , key_len , val_len ;
 const u_char * app_type_string ;
 size_t app_type_string_len ;
 int server_name_len ;
 ngx_str_t escaped_uri ;
 ngx_str_t * union_station_filters = NULL ;
 void * tmp ;
 ngx_uint_t i , n ;
 ngx_buf_t * b ;
 ngx_chain_t * cl , * body ;
 ngx_list_part_t * part ;
 ngx_table_elt_t * header ;
 ngx_http_script_code_pt code ;
 ngx_http_script_engine_t e , le ;
 ngx_http_core_srv_conf_t * cscf ;
 passenger_loc_conf_t * slcf ;
 passenger_context_t * context ;
 ngx_http_script_len_code_pt lcode ;
 cscf = ngx_http_get_module_srv_conf ( r , ngx_http_core_module ) ;
 slcf = ngx_http_get_module_loc_conf ( r , ngx_http_passenger_module ) ;
 context = ngx_http_get_module_ctx ( r , ngx_http_passenger_module ) ;
 if ( context == NULL ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 app_type_string = ( const u_char * ) pp_get_app_type_name ( context -> app_type ) ;
 app_type_string_len = strlen ( ( const char * ) app_type_string ) + 1 ;
 escaped_uri . len = * ngx_escape_uri ( NULL , r -> uri . data , r -> uri . len , NGX_ESCAPE_URI ) + r -> uri . len ;
 escaped_uri . data = ngx_pnalloc ( r -> pool , escaped_uri . len + 1 ) ;
 escaped_uri . data [ escaped_uri . len ] = '\0' ;
 ngx_escape_uri ( escaped_uri . data , r -> uri . data , r -> uri . len , NGX_ESCAPE_URI ) ;
 len = 0 ;
 if ( r -> headers_in . content_length_n >= 0 ) {
 len += sizeof ( "CONTENT_LENGTH" ) + uint_to_str ( r -> headers_in . content_length_n , buf , sizeof ( buf ) ) + 1 ;
 }
 len += sizeof ( "DOCUMENT_ROOT" ) + context -> public_dir . len + 1 ;
 if ( context -> base_uri . len > 0 ) {
 len += sizeof ( "SCRIPT_NAME" ) + context -> base_uri . len + 1 ;
 len += sizeof ( "RAILS_RELATIVE_URL_ROOT" ) + context -> base_uri . len + 1 ;
 len += sizeof ( "PATH_INFO" ) + escaped_uri . len - context -> base_uri . len + 1 ;
 }
 else {
 len += sizeof ( "SCRIPT_NAME" ) + sizeof ( "" ) ;
 len += sizeof ( "PATH_INFO" ) + escaped_uri . len + 1 ;
 }
 len += sizeof ( "REQUEST_URI" ) + escaped_uri . len + 1 ;
 if ( r -> args . len > 0 ) {
 len += 1 + r -> args . len ;
 }
 if ( r -> headers_in . host != NULL ) {
 tmp = memchr ( r -> headers_in . host -> value . data , ':' , r -> headers_in . host -> value . len ) ;
 if ( tmp == NULL ) {
 server_name_len = r -> headers_in . host -> value . len ;
 }
 else {
 server_name_len = ( int ) ( ( const u_char * ) tmp - r -> headers_in . host -> value . data ) ;
 }
 }
 else {
 server_name_len = cscf -> server_name . len ;
 }
 len += sizeof ( "SERVER_NAME" ) + server_name_len + 1 ;
 if ( r -> headers_in . content_type != NULL && r -> headers_in . content_type -> value . len > 0 ) {
 len += sizeof ( "CONTENT_TYPE" ) + r -> headers_in . content_type -> value . len + 1 ;
 }

 len += sizeof ( "HTTPS" ) + sizeof ( "on" ) ;
 }

 len += sizeof ( "PASSENGER_APP_TYPE" ) + app_type_string_len ;
 if ( slcf -> union_station_filters != NGX_CONF_UNSET_PTR && slcf -> union_station_filters -> nelts > 0 ) {
 len += sizeof ( "UNION_STATION_FILTERS" ) ;
 union_station_filters = ( ngx_str_t * ) slcf -> union_station_filters -> elts ;
 for ( i = 0 ;
 i < slcf -> union_station_filters -> nelts ;
 i ++ ) {
 if ( i != 0 ) {
 len ++ ;
 }
 len += union_station_filters [ i ] . len ;
 }
 len ++ ;
 }
 if ( slcf -> vars_len ) {
 ngx_memzero ( & le , sizeof ( ngx_http_script_engine_t ) ) ;
 ngx_http_script_flush_no_cacheable_variables ( r , slcf -> flushes ) ;
 le . flushed = 1 ;
 le . ip = slcf -> vars_len -> elts ;
 le . request = r ;
 while ( * ( uintptr_t * ) le . ip ) {
 lcode = * ( ngx_http_script_len_code_pt * ) le . ip ;
 key_len = lcode ( & le ) ;
 for ( val_len = 0 ;
 * ( uintptr_t * ) le . ip ;
 val_len += lcode ( & le ) ) {
 lcode = * ( ngx_http_script_len_code_pt * ) le . ip ;
 }
 le . ip += sizeof ( uintptr_t ) ;
 len += key_len + val_len ;
 }
 }
 if ( slcf -> upstream_config . pass_request_headers ) {
 part = & r -> headers_in . headers . part ;
 header = part -> elts ;
 for ( i = 0 ;
 ;
 i ++ ) {
 if ( i >= part -> nelts ) {
 if ( part -> next == NULL ) {
 break ;
 }
 part = part -> next ;
 header = part -> elts ;
 i = 0 ;
 }
 if ( ! header_is_transfer_encoding ( & header [ i ] . key ) ) {
 len += sizeof ( "HTTP_" ) - 1 + header [ i ] . key . len + 1 + header [ i ] . value . len + 1 ;
 }
 }
 }
 helper_agent_request_socket_password_data = pp_agents_starter_get_request_socket_password ( pp_agents_starter , & helper_agent_request_socket_password_len ) ;
 size = helper_agent_request_socket_password_len + len + 10 + 1 + 1 ;
 b = ngx_create_temp_buf ( r -> pool , size ) ;
 if ( b == NULL ) {
 return NGX_ERROR ;
 }
 cl = ngx_alloc_chain_link ( r -> pool ) ;
 if ( cl == NULL ) {
 return NGX_ERROR ;
 }
 cl -> buf = b ;
 b -> last = ngx_copy ( b -> last , helper_agent_request_socket_password_data , helper_agent_request_socket_password_len ) ;
 b -> last = ngx_snprintf ( b -> last , 10 , "%ui" , len ) ;
 * b -> last ++ = ( u_char ) ':' ;
 if ( r -> headers_in . content_length_n >= 0 ) {
 b -> last = ngx_copy ( b -> last , "CONTENT_LENGTH" , sizeof ( "CONTENT_LENGTH" ) ) ;
 b -> last = ngx_snprintf ( b -> last , 10 , "%O" , r -> headers_in . content_length_n ) ;
 * b -> last ++ = ( u_char ) 0 ;
 }
 b -> last = ngx_copy ( b -> last , "DOCUMENT_ROOT" , sizeof ( "DOCUMENT_ROOT" ) ) ;
 b -> last = ngx_copy ( b -> last , context -> public_dir . data , context -> public_dir . len + 1 ) ;
 if ( context -> base_uri . len > 0 ) {
 b -> last = ngx_copy ( b -> last , "SCRIPT_NAME" , sizeof ( "SCRIPT_NAME" ) ) ;
 b -> last = ngx_copy ( b -> last , context -> base_uri . data , context -> base_uri . len + 1 ) ;
 b -> last = ngx_copy ( b -> last , "RAILS_RELATIVE_URL_ROOT" , sizeof ( "RAILS_RELATIVE_URL_ROOT" ) ) ;
 b -> last = ngx_copy ( b -> last , context -> base_uri . data , context -> base_uri . len + 1 ) ;
 b -> last = ngx_copy ( b -> last , "PATH_INFO" , sizeof ( "PATH_INFO" ) ) ;
 b -> last = ngx_copy ( b -> last , escaped_uri . data + context -> base_uri . len , escaped_uri . len - context -> base_uri . len ) ;
 b -> last = ngx_copy ( b -> last , "" , 1 ) ;
 }
 else {
 b -> last = ngx_copy ( b -> last , "SCRIPT_NAME" , sizeof ( "SCRIPT_NAME" ) ) ;
 b -> last = ngx_copy ( b -> last , "" , sizeof ( "" ) ) ;
 b -> last = ngx_copy ( b -> last , "PATH_INFO" , sizeof ( "PATH_INFO" ) ) ;
 b -> last = ngx_copy ( b -> last , escaped_uri . data , escaped_uri . len ) ;
 b -> last = ngx_copy ( b -> last , "" , 1 ) ;
 }
 b -> last = ngx_copy ( b -> last , "REQUEST_URI" , sizeof ( "REQUEST_URI" ) ) ;
 b -> last = ngx_copy ( b -> last , escaped_uri . data , escaped_uri . len ) ;
 if ( r -> args . len > 0 ) {
 b -> last = ngx_copy ( b -> last , "?" , 1 ) ;
 b -> last = ngx_copy ( b -> last , r -> args . data , r -> args . len ) ;
 }
 b -> last = ngx_copy ( b -> last , "" , 1 ) ;
 b -> last = ngx_copy ( b -> last , "SERVER_NAME" , sizeof ( "SERVER_NAME" ) ) ;
 if ( r -> headers_in . host != NULL ) {
 b -> last = ngx_copy ( b -> last , r -> headers_in . host -> value . data , server_name_len ) ;
 }
 else {
 b -> last = ngx_copy ( b -> last , cscf -> server_name . data , server_name_len ) ;
 }
 b -> last = ngx_copy ( b -> last , "" , 1 ) ;
 if ( r -> headers_in . content_type != NULL && r -> headers_in . content_type -> value . len > 0 ) {
 b -> last = ngx_copy ( b -> last , "CONTENT_TYPE" , sizeof ( "CONTENT_TYPE" ) ) ;
 b -> last = ngx_copy ( b -> last , r -> headers_in . content_type -> value . data , r -> headers_in . content_type -> value . len ) ;
 b -> last = ngx_copy ( b -> last , "" , 1 ) ;
 }

 b -> last = ngx_copy ( b -> last , "HTTPS" , sizeof ( "HTTPS" ) ) ;
 b -> last = ngx_copy ( b -> last , "on" , sizeof ( "on" ) ) ;
 }

 b -> last = ngx_copy ( b -> last , "PASSENGER_APP_TYPE" , sizeof ( "PASSENGER_APP_TYPE" ) ) ;
 b -> last = ngx_copy ( b -> last , app_type_string , app_type_string_len ) ;
 if ( slcf -> union_station_filters != NGX_CONF_UNSET_PTR && slcf -> union_station_filters -> nelts > 0 ) {
 b -> last = ngx_copy ( b -> last , "UNION_STATION_FILTERS" , sizeof ( "UNION_STATION_FILTERS" ) ) ;
 for ( i = 0 ;
 i < slcf -> union_station_filters -> nelts ;
 i ++ ) {
 if ( i != 0 ) {
 b -> last = ngx_copy ( b -> last , "\1" , 1 ) ;
 }
 b -> last = ngx_copy ( b -> last , union_station_filters [ i ] . data , union_station_filters [ i ] . len ) ;
 }
 b -> last = ngx_copy ( b -> last , "\0" , 1 ) ;
 }
 if ( slcf -> vars_len ) {
 ngx_memzero ( & e , sizeof ( ngx_http_script_engine_t ) ) ;
 e . ip = slcf -> vars -> elts ;
 e . pos = b -> last ;
 e . request = r ;
 e . flushed = 1 ;
 le . ip = slcf -> vars_len -> elts ;
 while ( * ( uintptr_t * ) le . ip ) {
 lcode = * ( ngx_http_script_len_code_pt * ) le . ip ;
 ( void ) lcode ( & le ) ;
 for ( val_len = 0 ;
 * ( uintptr_t * ) le . ip ;
 val_len += lcode ( & le ) ) {
 lcode = * ( ngx_http_script_len_code_pt * ) le . ip ;
 }
 le . ip += sizeof ( uintptr_t ) ;
 while ( * ( uintptr_t * ) e . ip ) {
 code = * ( ngx_http_script_code_pt * ) e . ip ;
 code ( ( ngx_http_script_engine_t * ) & e ) ;
 }
 e . ip += sizeof ( uintptr_t ) ;
 }
 b -> last = e . pos ;
 }
 if ( slcf -> upstream_config . pass_request_headers ) {
 part = & r -> headers_in . headers . part ;
 header = part -> elts ;
 for ( i = 0 ;
 ;
 i ++ ) {
 if ( i >= part -> nelts ) {
 if ( part -> next == NULL ) {
 break ;
 }
 part = part -> next ;
 header = part -> elts ;
 i = 0 ;
 }
 if ( header_is_transfer_encoding ( & header [ i ] . key ) ) {
 continue ;
 }
 b -> last = ngx_cpymem ( b -> last , "HTTP_" , sizeof ( "HTTP_" ) - 1 ) ;
 for ( n = 0 ;
 n < header [ i ] . key . len ;
 n ++ ) {
 ch = header [ i ] . key . data [ n ] ;
 if ( ch >= 'a' && ch <= 'z' ) {
 ch &= ~ 0x20 ;
 }
 else if ( ch == '-' ) {
 ch = '_' ;
 }
 * b -> last ++ = ch ;
 }
 * b -> last ++ = ( u_char ) 0 ;
 b -> last = ngx_copy ( b -> last , header [ i ] . value . data , header [ i ] . value . len ) ;
 * b -> last ++ = ( u_char ) 0 ;
 }
 }
 * b -> last ++ = ( u_char ) ',' ;
 if ( slcf -> upstream_config . pass_request_body ) {
 body = r -> upstream -> request_bufs ;
 r -> upstream -> request_bufs = cl ;
 while ( body ) {
 b = ngx_alloc_buf ( r -> pool ) ;
 if ( b == NULL ) {
 return NGX_ERROR ;
 }
 ngx_memcpy ( b , body -> buf , sizeof ( ngx_buf_t ) ) ;
 cl -> next = ngx_alloc_chain_link ( r -> pool ) ;
 if ( cl -> next == NULL ) {
 return NGX_ERROR ;
 }
 cl = cl -> next ;
 cl -> buf = b ;
 body = body -> next ;
 }
 b -> flush = 1 ;
 }
 else {
 r -> upstream -> request_bufs = cl ;
 }
 cl -> next = NULL ;
 return NGX_OK ;
 }