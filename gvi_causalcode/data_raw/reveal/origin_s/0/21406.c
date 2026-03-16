static int dissect_opcua ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 tcp_dissect_pdus ( tvb , pinfo , tree , TRUE , FRAME_HEADER_LEN , get_opcua_message_len , dissect_opcua_message , data ) ;
 return tvb_reported_length ( tvb ) ;
 }