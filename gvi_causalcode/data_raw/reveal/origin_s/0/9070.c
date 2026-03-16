static void abort_request ( ngx_http_request_t * r ) {
 ngx_log_debug0 ( NGX_LOG_DEBUG_HTTP , r -> connection -> log , 0 , "abort Passenger request" ) ;
 }