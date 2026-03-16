static int dissect_pkt_ccc ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 proto_item * ti = NULL ;
 proto_tree * pkt_ccc_tree = NULL ;
 if ( tree ) {
 ti = proto_tree_add_item ( tree , proto_pkt_ccc , tvb , 0 , 12 , ENC_NA ) ;
 pkt_ccc_tree = proto_item_add_subtree ( ti , ett_pkt_ccc ) ;
 proto_tree_add_item ( pkt_ccc_tree , hf_pkt_ccc_id , tvb , 0 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( pkt_ccc_tree , hf_pkt_ccc_ts , tvb , 4 , 8 , ENC_TIME_NTP | ENC_BIG_ENDIAN ) ;
 }
 return dissect_rtp ( tvb , pinfo , tree , data ) ;
 }