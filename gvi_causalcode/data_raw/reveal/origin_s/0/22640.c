static gboolean is_mpa_req ( tvbuff_t * tvb , packet_info * pinfo ) {
 conversation_t * conversation = NULL ;
 mpa_state_t * state = NULL ;
 guint8 mcrres ;
 if ( tvb_get_ntoh64 ( tvb , 0 ) != MPA_REQ_REP_FRAME || tvb_get_ntoh64 ( tvb , 8 ) != MPA_ID_REQ_FRAME ) return FALSE ;
 conversation = find_or_create_conversation ( pinfo ) ;
 if ( ! get_mpa_state ( conversation ) ) {
 state = init_mpa_state ( ) ;
 mcrres = tvb_get_guint8 ( tvb , 16 ) ;
 state -> ini_exp_m_res = mcrres & MPA_MARKER_FLAG ;
 state -> crc = mcrres & MPA_CRC_FLAG ;
 state -> revision = tvb_get_guint8 ( tvb , 17 ) ;
 state -> req_frame_num = pinfo -> num ;
 state -> minfo [ MPA_INITIATOR ] . port = pinfo -> srcport ;
 state -> minfo [ MPA_RESPONDER ] . port = pinfo -> destport ;
 conversation_add_proto_data ( conversation , proto_iwarp_mpa , state ) ;
 if ( mcrres & MPA_RESERVED_FLAG ) expert_add_info ( pinfo , NULL , & ei_mpa_res_field_not_set0 ) ;
 if ( state -> revision != 1 ) expert_add_info ( pinfo , NULL , & ei_mpa_rev_field_not_set1 ) ;
 }
 return TRUE ;
 }