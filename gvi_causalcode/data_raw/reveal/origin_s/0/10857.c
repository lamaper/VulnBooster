static guint16 de_bcc_orig_ind ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_spare_3 , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_orig_ind , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }