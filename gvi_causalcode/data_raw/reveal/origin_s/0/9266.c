static void export_diameter_pdu ( packet_info * pinfo , tvbuff_t * tvb ) {
 exp_pdu_data_t * exp_pdu_data ;
 guint8 tags_bit_field ;
 tags_bit_field = EXP_PDU_TAG_IP_SRC_BIT + EXP_PDU_TAG_IP_DST_BIT + EXP_PDU_TAG_SRC_PORT_BIT + EXP_PDU_TAG_DST_PORT_BIT + EXP_PDU_TAG_ORIG_FNO_BIT ;
 exp_pdu_data = load_export_pdu_tags ( pinfo , EXP_PDU_TAG_PROTO_NAME , "diameter" , & tags_bit_field , 1 ) ;
 exp_pdu_data -> tvb_captured_length = tvb_captured_length ( tvb ) ;
 exp_pdu_data -> tvb_reported_length = tvb_reported_length ( tvb ) ;
 exp_pdu_data -> pdu_tvb = tvb ;
 tap_queue_packet ( exported_pdu_tap , pinfo , exp_pdu_data ) ;
 }