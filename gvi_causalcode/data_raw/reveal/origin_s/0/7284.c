guint16 de_cs_domain_spec_sys_info ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_rr_t3212 , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) , 7 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_att , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }