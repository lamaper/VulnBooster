static int request_reissue ( struct request * req ) {
 const struct nameserver * const last_ns = req -> ns ;
 req -> ns = nameserver_pick ( ) ;
 if ( req -> ns == last_ns ) {
 return 1 ;
 }
 req -> reissue_count ++ ;
 req -> tx_count = 0 ;
 req -> transmit_me = 1 ;
 return 0 ;
 }