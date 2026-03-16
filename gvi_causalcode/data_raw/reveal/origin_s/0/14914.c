static gboolean dissect_q931_tpkt_heur ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 int lv_tpkt_len ;
 lv_tpkt_len = is_tpkt ( tvb , 3 ) ;
 if ( lv_tpkt_len == - 1 ) {
 return FALSE ;
 }
 if ( tvb_reported_length ( tvb ) == 4 ) {
 dissect_tpkt_encap ( tvb , pinfo , tree , q931_desegment , q931_tpkt_pdu_handle ) ;
 return TRUE ;
 }
 if ( ! tvb_bytes_exist ( tvb , 4 , 3 ) ) return FALSE ;
 if ( ( tvb_get_guint8 ( tvb , 4 ) != NLPID_Q_931 ) && ( tvb_get_guint8 ( tvb , 4 ) != 0x03 ) ) {
 return FALSE ;
 }
 dissect_tpkt_encap ( tvb , pinfo , tree , q931_desegment , q931_tpkt_pdu_handle ) ;
 return TRUE ;
 }