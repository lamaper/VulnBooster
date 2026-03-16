static void dissect_h245_h245 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * parent_tree ) {
 proto_item * it ;
 proto_tree * tr ;
 guint32 offset = 0 ;
 asn1_ctx_t asn1_ctx ;
 fast_start = FALSE ;
 upcoming_olc = NULL ;
 upcoming_channel = NULL ;
 codec_type = NULL ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , PSNAME ) ;
 it = proto_tree_add_protocol_format ( parent_tree , proto_h245 , tvb , 0 , tvb_length ( tvb ) , PSNAME ) ;
 tr = proto_item_add_subtree ( it , ett_h245 ) ;
 while ( tvb_length_remaining ( tvb , offset >> 3 ) > 0 ) {
 CLEANUP_PUSH ( reset_h245_pi , NULL ) ;
 h245_pi = wmem_new ( wmem_packet_scope ( ) , h245_packet_info ) ;
 init_h245_packet_info ( h245_pi ) ;
 asn1_ctx_init ( & asn1_ctx , ASN1_ENC_PER , TRUE , pinfo ) ;
 offset = dissect_h245_MultimediaSystemControlMessage ( tvb , offset , & asn1_ctx , tr , hf_h245_pdu_type ) ;
 tap_queue_packet ( h245dg_tap , pinfo , h245_pi ) ;
 offset = ( offset + 0x07 ) & 0xfffffff8 ;
 CLEANUP_CALL_AND_POP ;
 }
 }