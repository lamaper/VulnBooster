static guint16 de_bcc_state_attr ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_state_attr , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_state_attr_da , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_state_attr_ua , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_state_attr_comm , tvb , offset , 1 , ENC_NA ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_state_attr_oi , tvb , offset , 1 , ENC_NA ) ;
 return 1 ;
 }