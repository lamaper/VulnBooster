static guint16 de_tp_epc_horizontal_velocity ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_bearing , tvb , curr_offset << 3 , 9 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_horizontal_speed , tvb , ( curr_offset << 3 ) + 9 , 11 , ENC_BIG_ENDIAN ) ;
 curr_offset += 3 ;
 return ( curr_offset - offset ) ;
 }