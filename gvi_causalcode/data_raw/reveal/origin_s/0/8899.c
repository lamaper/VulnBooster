static int dissect_dns_tcp_pdu ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "DNS" ) ;
 dissect_dns_common ( tvb , pinfo , tree , TRUE , FALSE , FALSE ) ;
 return tvb_reported_length ( tvb ) ;
 }