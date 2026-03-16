static int dissect_pcp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 tcp_dissect_pdus ( tvb , pinfo , tree , TRUE , PCP_HEADER_LEN , get_pcp_message_len , dissect_pcp_message , data ) ;
 return tvb_captured_length ( tvb ) ;
 }