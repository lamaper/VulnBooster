static int dissect_rsl_ie_cmd_ind ( tvbuff_t * tvb , packet_info * pinfo _U_ , proto_tree * tree , int offset , gboolean is_mandatory ) {
 proto_tree * ie_tree ;
 guint8 ie_id ;
 guint8 octet ;
 if ( is_mandatory == FALSE ) {
 ie_id = tvb_get_guint8 ( tvb , offset ) ;
 if ( ie_id != RSL_IE_CMD_IND ) return offset ;
 }
 ie_tree = proto_tree_add_subtree ( tree , tvb , offset , 2 , ett_ie_cmd_ind , NULL , "Command indicator IE" ) ;
 proto_tree_add_item ( ie_tree , hf_rsl_ie_id , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 proto_tree_add_item ( ie_tree , hf_rsl_extension_bit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ( octet & 0x80 ) == 0x80 ) {
 proto_tree_add_item ( ie_tree , hf_rsl_command , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 offset = offset + 2 ;
 }
 else {
 proto_tree_add_item ( ie_tree , hf_rsl_command , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 offset ++ ;
 }
 return offset ;
 }