static void nameserver_send_probe ( struct nameserver * const ns ) {
 struct request * req ;
 log ( EVDNS_LOG_DEBUG , "Sending probe to %s" , debug_ntoa ( ns -> address ) ) ;
 req = request_new ( TYPE_A , "www.google.com" , DNS_QUERY_NO_SEARCH , nameserver_probe_callback , ns ) ;
 if ( ! req ) return ;
 request_trans_id_set ( req , transaction_id_pick ( ) ) ;
 req -> ns = ns ;
 request_submit ( req ) ;
 }