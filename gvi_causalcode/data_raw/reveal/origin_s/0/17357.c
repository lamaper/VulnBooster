static void dissect_t38_tcp ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 primary_part = TRUE ;
 if ( t38_tpkt_usage == T38_TPKT_ALWAYS ) {
 dissect_tpkt_encap ( tvb , pinfo , tree , t38_tpkt_reassembly , t38_tcp_pdu_handle ) ;
 }
 else if ( ( t38_tpkt_usage == T38_TPKT_NEVER ) || ( is_tpkt ( tvb , 1 ) == - 1 ) ) {
 dissect_t38_tcp_pdu ( tvb , pinfo , tree ) ;
 }
 else {
 dissect_tpkt_encap ( tvb , pinfo , tree , t38_tpkt_reassembly , t38_tcp_pdu_handle ) ;
 }
 }