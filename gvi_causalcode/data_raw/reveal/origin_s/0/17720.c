guint16 de_serv_cat ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b7 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b6 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b5 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b4 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b3 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b2 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_serv_cat_b1 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return len ;
 }