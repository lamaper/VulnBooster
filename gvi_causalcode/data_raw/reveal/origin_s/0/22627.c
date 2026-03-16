static int config_filters_request ( struct config_connection * conn ) {
 struct config_filter_parser * const * filters = config_filter_get_all ( config_filter ) ;
 o_stream_cork ( conn -> output ) ;
 while ( * filters != NULL ) {
 const struct config_filter * filter = & ( * filters ) -> filter ;
 o_stream_nsend_str ( conn -> output , "FILTER" ) ;
 if ( filter -> service != NULL ) o_stream_nsend_str ( conn -> output , t_strdup_printf ( "\tservice=%s" , filter -> service ) ) ;
 if ( filter -> local_name != NULL ) o_stream_nsend_str ( conn -> output , t_strdup_printf ( "\tlocal-name=%s" , filter -> local_name ) ) ;
 if ( filter -> local_bits > 0 ) o_stream_nsend_str ( conn -> output , t_strdup_printf ( "\tlocal-net=%s/%u" , net_ip2addr ( & filter -> local_net ) , filter -> local_bits ) ) ;
 if ( filter -> remote_bits > 0 ) o_stream_nsend_str ( conn -> output , t_strdup_printf ( "\tremote-net=%s/%u" , net_ip2addr ( & filter -> remote_net ) , filter -> remote_bits ) ) ;
 o_stream_nsend_str ( conn -> output , "\n" ) ;
 filters ++ ;
 }
 o_stream_nsend_str ( conn -> output , "\n" ) ;
 o_stream_uncork ( conn -> output ) ;
 return 0 ;
 }