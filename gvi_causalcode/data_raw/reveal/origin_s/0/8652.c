guint16 de_d_gb_call_ref ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_group_call_reference , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_service_flag , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_af_acknowledgement , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_call_priority , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 curr_offset += 4 ;
 proto_tree_add_item ( tree , hf_gsm_a_ciphering_info , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 4 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }