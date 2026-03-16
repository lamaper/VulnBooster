static guint16 de_add_upd_params ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_csmo , tvb , ( curr_offset << 3 ) + 6 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_dtap_csmt , tvb , ( curr_offset << 3 ) + 7 , 1 , ENC_BIG_ENDIAN ) ;
 return ( len ) ;
 }