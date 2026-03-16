static ngx_int_t process_header ( ngx_http_request_t * r ) {
 ngx_str_t * status_line ;
 ngx_int_t rc , status ;
 ngx_table_elt_t * h ;
 ngx_http_upstream_t * u ;
 ngx_http_upstream_header_t * hh ;
 ngx_http_upstream_main_conf_t * umcf ;
 ngx_http_core_loc_conf_t * clcf ;
 passenger_loc_conf_t * slcf ;
 umcf = ngx_http_get_module_main_conf ( r , ngx_http_upstream_module ) ;
 clcf = ngx_http_get_module_loc_conf ( r , ngx_http_core_module ) ;
 slcf = ngx_http_get_module_loc_conf ( r , ngx_http_passenger_module ) ;
 for ( ;
 ;
 ) {
 rc = ngx_http_parse_header_line ( r , & r -> upstream -> buffer , 1 ) ;
 if ( rc == NGX_OK ) {
 h = ngx_list_push ( & r -> upstream -> headers_in . headers ) ;
 if ( h == NULL ) {
 return NGX_ERROR ;
 }
 h -> hash = r -> header_hash ;
 h -> key . len = r -> header_name_end - r -> header_name_start ;
 h -> value . len = r -> header_end - r -> header_start ;
 h -> key . data = ngx_pnalloc ( r -> pool , h -> key . len + 1 + h -> value . len + 1 + h -> key . len ) ;
 if ( h -> key . data == NULL ) {
 return NGX_ERROR ;
 }
 h -> value . data = h -> key . data + h -> key . len + 1 ;
 h -> lowcase_key = h -> key . data + h -> key . len + 1 + h -> value . len + 1 ;
 ngx_memcpy ( h -> key . data , r -> header_name_start , h -> key . len ) ;
 h -> key . data [ h -> key . len ] = '\0' ;
 ngx_memcpy ( h -> value . data , r -> header_start , h -> value . len ) ;
 h -> value . data [ h -> value . len ] = '\0' ;
 if ( h -> key . len == r -> lowcase_index ) {
 ngx_memcpy ( h -> lowcase_key , r -> lowcase_header , h -> key . len ) ;
 }
 else {
 ngx_strlow ( h -> lowcase_key , h -> key . data , h -> key . len ) ;
 }
 hh = ngx_hash_find ( & umcf -> headers_in_hash , h -> hash , h -> lowcase_key , h -> key . len ) ;
 if ( hh && hh -> handler ( r , h , hh -> offset ) != NGX_OK ) {
 return NGX_ERROR ;
 }
 ngx_log_debug2 ( NGX_LOG_DEBUG_HTTP , r -> connection -> log , 0 , "http scgi header: \"%V: %V\"" , & h -> key , & h -> value ) ;
 continue ;
 }
 if ( rc == NGX_HTTP_PARSE_HEADER_DONE ) {
 ngx_log_debug0 ( NGX_LOG_DEBUG_HTTP , r -> connection -> log , 0 , "http scgi header done" ) ;
 if ( r -> upstream -> headers_in . server == NULL ) {
 h = ngx_list_push ( & r -> upstream -> headers_in . headers ) ;
 if ( h == NULL ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 h -> hash = ngx_hash ( ngx_hash ( ngx_hash ( ngx_hash ( ngx_hash ( 's' , 'e' ) , 'r' ) , 'v' ) , 'e' ) , 'r' ) ;
 h -> key . len = sizeof ( "Server" ) - 1 ;
 h -> key . data = ( u_char * ) "Server" ;
 if ( slcf -> show_version_in_header == 0 ) {
 if ( clcf -> server_tokens ) {
 h -> value . data = ( u_char * ) ( NGINX_VER " + Phusion Passenger" ) ;
 }
 else {
 h -> value . data = ( u_char * ) ( "nginx + Phusion Passenger" ) ;
 }
 }
 else {
 if ( clcf -> server_tokens ) {
 h -> value . data = ( u_char * ) ( NGINX_VER " + Phusion Passenger " PASSENGER_VERSION ) ;
 }
 else {
 h -> value . data = ( u_char * ) ( "nginx + Phusion Passenger " PASSENGER_VERSION ) ;
 }
 }
 h -> value . len = ngx_strlen ( h -> value . data ) ;
 h -> lowcase_key = ( u_char * ) "server" ;
 }
 if ( r -> upstream -> headers_in . date == NULL ) {
 h = ngx_list_push ( & r -> upstream -> headers_in . headers ) ;
 if ( h == NULL ) {
 return NGX_HTTP_INTERNAL_SERVER_ERROR ;
 }
 h -> hash = ngx_hash ( ngx_hash ( ngx_hash ( 'd' , 'a' ) , 't' ) , 'e' ) ;
 h -> key . len = sizeof ( "Date" ) - 1 ;
 h -> key . data = ( u_char * ) "Date" ;
 h -> value . len = 0 ;
 h -> value . data = NULL ;
 h -> lowcase_key = ( u_char * ) "date" ;
 }
 u = r -> upstream ;
 if ( u -> headers_in . status_n ) {
 goto done ;
 }
 if ( u -> headers_in . status ) {
 status_line = & u -> headers_in . status -> value ;
 status = ngx_atoi ( status_line -> data , 3 ) ;
 if ( status == NGX_ERROR ) {
 ngx_log_error ( NGX_LOG_ERR , r -> connection -> log , 0 , "upstream sent invalid status \"%V\"" , status_line ) ;
 return NGX_HTTP_UPSTREAM_INVALID_HEADER ;
 }
 u -> headers_in . status_n = status ;
 u -> headers_in . status_line = * status_line ;
 }
 else if ( u -> headers_in . location ) {
 u -> headers_in . status_n = 302 ;
 ngx_str_set ( & u -> headers_in . status_line , "302 Moved Temporarily" ) ;
 }
 else {
 u -> headers_in . status_n = 200 ;
 ngx_str_set ( & u -> headers_in . status_line , "200 OK" ) ;
 }
 if ( u -> state ) {
 u -> state -> status = u -> headers_in . status_n ;
 }
 done : # ifdef NGX_HTTP_SWITCHING_PROTOCOLS if ( u -> headers_in . status_n == NGX_HTTP_SWITCHING_PROTOCOLS && r -> headers_in . upgrade ) {
 u -> upgrade = 1 ;
 }

 }
 if ( rc == NGX_AGAIN ) {
 return NGX_AGAIN ;
 }
 ngx_log_error ( NGX_LOG_ERR , r -> connection -> log , 0 , "upstream sent invalid header" ) ;
 return NGX_HTTP_UPSTREAM_INVALID_HEADER ;
 }
 }