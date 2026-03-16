static gboolean dissect_class_svalidator_heur ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 unsigned char service , service_code , ioilen , segment ;
 cip_req_info_t * preq_info ;
 guint32 classid = 0 ;
 int offset = 0 ;
 service = tvb_get_guint8 ( tvb , offset ) ;
 service_code = service & 0x7F ;
 if ( service_code == SC_GET_ATT_ALL ) {
 if ( service & 0x80 ) {
 preq_info = ( cip_req_info_t * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_cip , 0 ) ;
 if ( ( preq_info != NULL ) && ( preq_info -> dissector == dissector_get_uint_handle ( subdissector_class_table , CI_CLS_SAFETY_VALIDATOR ) ) ) {
 call_dissector ( preq_info -> dissector , tvb , pinfo , tree ) ;
 return TRUE ;
 }
 }
 else {
 ioilen = tvb_get_guint8 ( tvb , offset + 1 ) ;
 if ( ioilen > 1 ) {
 segment = tvb_get_guint8 ( tvb , offset + 2 ) ;
 if ( ( ( segment & CI_SEGMENT_TYPE_MASK ) == CI_LOGICAL_SEGMENT ) && ( ( segment & CI_LOGICAL_SEG_TYPE_MASK ) == CI_LOGICAL_SEG_CLASS_ID ) ) {
 switch ( segment & CI_LOGICAL_SEG_FORMAT_MASK ) {
 case CI_LOGICAL_SEG_8_BIT : classid = tvb_get_guint8 ( tvb , offset + 3 ) ;
 break ;
 case CI_LOGICAL_SEG_16_BIT : if ( ioilen >= 2 ) classid = tvb_get_letohs ( tvb , offset + 4 ) ;
 break ;
 case CI_LOGICAL_SEG_32_BIT : if ( ioilen >= 3 ) classid = tvb_get_letohl ( tvb , offset + 4 ) ;
 break ;
 }
 }
 }
 if ( classid == CI_CLS_SAFETY_VALIDATOR ) {
 call_dissector ( cip_class_s_validator_handle , tvb , pinfo , tree ) ;
 return TRUE ;
 }
 }
 }
 return FALSE ;
 }