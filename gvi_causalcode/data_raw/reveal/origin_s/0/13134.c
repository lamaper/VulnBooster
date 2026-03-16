static guint16 de_nas_cont_for_ps_ho ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_old_xid , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_type_of_ciph_alg , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 proto_tree_add_item ( tree , hf_gsm_a_iov_ui , tvb , curr_offset , 4 , ENC_BIG_ENDIAN ) ;
 curr_offset += 4 ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }