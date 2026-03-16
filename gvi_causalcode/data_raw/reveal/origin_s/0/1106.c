static guint16 de_tp_epc_ue_test_loop_mode ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 bit_offset ;
 curr_offset = offset ;
 bit_offset = curr_offset << 3 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , bit_offset , 6 , ENC_BIG_ENDIAN ) ;
 bit_offset += 6 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_epc_ue_tl_mode , tvb , bit_offset , 2 , ENC_BIG_ENDIAN ) ;
 epc_test_loop_mode = tvb_get_guint8 ( tvb , curr_offset ) & 0x03 ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }