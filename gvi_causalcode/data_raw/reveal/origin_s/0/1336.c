static void dissect_h245 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree ) {
 dissect_tpkt_encap ( tvb , pinfo , parent_tree , h245_reassembly , MultimediaSystemControlMessage_handle ) ;
 }