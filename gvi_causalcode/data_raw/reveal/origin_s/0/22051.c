static guint16 de_bcc_call_state ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_bcc_call_state , tvb , offset , 2 , ENC_NA ) ;
 return 1 ;
 }