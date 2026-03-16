static int dissect_dns_tcp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 tcp_dissect_pdus ( tvb , pinfo , tree , dns_desegment , 2 , get_dns_pdu_len , dissect_dns_tcp_pdu , data ) ;
 return tvb_reported_length ( tvb ) ;
 }