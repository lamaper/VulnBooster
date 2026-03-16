static guint16 de_bcc_cause ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 int curr_len ;
 curr_len = len ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_cause_structure , tvb , curr_offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_cause , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset ++ ;
 curr_len -- ;
 EXTRANEOUS_DATA_CHECK ( curr_len , 0 , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }