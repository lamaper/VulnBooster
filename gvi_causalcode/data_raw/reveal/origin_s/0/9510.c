static ngx_int_t process_status_line ( ngx_http_request_t * r ) {
 ngx_int_t rc ;
 ngx_http_upstream_t * u ;
 passenger_context_t * context ;
 context = ngx_http_get_module_ctx ( r , ngx_http_passenger_module ) ;
 if ( context == NULL ) {
 return NGX_ERROR ;
 }
 rc = parse_status_line ( r , context ) ;
 if ( rc == NGX_AGAIN ) {
 return rc ;
 }
 u = r -> upstream ;
 if ( rc == NGX_HTTP_SCGI_PARSE_NO_HEADER ) {
 ngx_log_error ( NGX_LOG_ERR , r -> connection -> log , 0 , "upstream sent no valid HTTP/1.0 header" ) ;

 return NGX_HTTP_UPSTREAM_INVALID_HEADER ;
 }

 u -> state -> status = NGX_HTTP_OK ;
 return NGX_OK ;
 }
 u -> headers_in . status_n = context -> status ;
 u -> state -> status = context -> status ;
 u -> headers_in . status_line . len = context -> status_end - context -> status_start ;
 u -> headers_in . status_line . data = ngx_palloc ( r -> pool , u -> headers_in . status_line . len ) ;
 if ( u -> headers_in . status_line . data == NULL ) {
 return NGX_ERROR ;
 }
 ngx_memcpy ( u -> headers_in . status_line . data , context -> status_start , u -> headers_in . status_line . len ) ;
 ngx_log_debug2 ( NGX_LOG_DEBUG_HTTP , r -> connection -> log , 0 , "http scgi status %ui \"%V\"" , u -> headers_in . status_n , & u -> headers_in . status_line ) ;
 u -> process_header = process_header ;
 return process_header ( r ) ;
 }