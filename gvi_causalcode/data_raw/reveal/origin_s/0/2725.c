static void dissect_dns_sctp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "DNS" ) ;
 dissect_dns_common ( tvb , pinfo , tree , FALSE , FALSE , FALSE ) ;
 }