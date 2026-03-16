static ngx_int_t reinit_request ( ngx_http_request_t * r ) {
 passenger_context_t * context ;
 context = ngx_http_get_module_ctx ( r , ngx_http_passenger_module ) ;
 if ( context == NULL ) {
 return NGX_OK ;
 }
 context -> status = 0 ;
 context -> status_count = 0 ;
 context -> status_start = NULL ;
 context -> status_end = NULL ;
 r -> upstream -> process_header = process_status_line ;
 r -> state = 0 ;
 return NGX_OK ;
 }