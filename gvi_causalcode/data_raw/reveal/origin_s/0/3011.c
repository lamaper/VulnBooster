static int dissect_rsl_ie_cbch_load_inf ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_item * item ;
 proto_tree * ie_tree ;
 guint8 ie_id ;
 guint8 octet ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_CBCH_LOAD_INF ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 0 , ett_ie_cbch_load_inf , NULL , "CBCH Load Information IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_cbch_load_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 item = proto_tree_add_item ( ie_tree , hf_rsl_msg_slt_cnt , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( ( octet & 0x80 ) == 0x80 ) {
 proto_item_append_text ( item , "The amount of SMSCB messages (1 to 15) that are needed immediately by BTS" ) ;
 }
 else {
 proto_item_append_text ( item , "The amount of delay in message slots (1 to 15) that is needed immediately by BTS" ) ;
 }
 offset ++ ;
 return offset ;
 }