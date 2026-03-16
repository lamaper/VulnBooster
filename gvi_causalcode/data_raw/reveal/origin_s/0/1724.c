static guint16 de_pd_sapi ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 proto_tree * subtree ;
 curr_offset = offset ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 1 , ett_gsm_dtap_elem [ DE_PD_SAPI ] , NULL , val_to_str_ext_const ( DE_PD_SAPI , & gsm_dtap_elem_strings_ext , "" ) ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_sapi , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_L3_protocol_discriminator , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }