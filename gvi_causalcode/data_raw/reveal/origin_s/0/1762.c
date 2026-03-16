static guint16 de_aux_states ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_extension , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_hold_auxiliary_state , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_multi_party_auxiliary_state , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }