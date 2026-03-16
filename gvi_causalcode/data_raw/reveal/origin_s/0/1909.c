static gboolean dissect_rtmpt_heur ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 conversation_t * conversation ;
 if ( tvb_reported_length ( tvb ) >= 12 ) {
 struct tcpinfo * tcpinfo = ( struct tcpinfo * ) data ;
 if ( tcpinfo -> lastackseq == RTMPT_HANDSHAKE_OFFSET_2 && tcpinfo -> seq == RTMPT_HANDSHAKE_OFFSET_1 && tvb_get_guint8 ( tvb , 0 ) == RTMPT_MAGIC ) {
 conversation = find_or_create_conversation ( pinfo ) ;
 conversation_set_dissector ( conversation , rtmpt_tcp_handle ) ;
 dissect_rtmpt_tcp ( tvb , pinfo , tree , data ) ;
 return TRUE ;
 }
 }
 return FALSE ;
 }