static gboolean is_mpa_rep ( tvbuff_t * tvb , packet_info * pinfo ) {
 conversation_t * conversation = NULL ;
 mpa_state_t * state = NULL ;
 guint8 mcrres ;
 if ( tvb_get_ntoh64 ( tvb , 0 ) != MPA_REQ_REP_FRAME || tvb_get_ntoh64 ( tvb , 8 ) != MPA_ID_REP_FRAME ) {
 return FALSE ;
 }
 conversation = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , pinfo -> srcport , pinfo -> destport , 0 ) ;
 if ( ! conversation ) {
 return FALSE ;
 }
 state = get_mpa_state ( conversation ) ;
 if ( ! state ) {
 return FALSE ;
 }
 if ( ! state -> full_operation ) {
 mcrres = tvb_get_guint8 ( tvb , 16 ) ;
 state -> res_exp_m_ini = mcrres & MPA_MARKER_FLAG ;
 state -> crc = state -> crc | ( mcrres & MPA_CRC_FLAG ) ;
 state -> rep_frame_num = pinfo -> num ;
 if ( ! ( mcrres & MPA_REJECT_FLAG ) ) state -> full_operation = TRUE ;
 else expert_add_info ( pinfo , NULL , & ei_mpa_reject_bit_responder ) ;
 }
 return TRUE ;
 }