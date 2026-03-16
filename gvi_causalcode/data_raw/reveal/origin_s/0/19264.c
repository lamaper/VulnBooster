static void dissect_mdns_udp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "MDNS" ) ;
 dissect_dns_common ( tvb , pinfo , tree , FALSE , TRUE , FALSE ) ;
 }