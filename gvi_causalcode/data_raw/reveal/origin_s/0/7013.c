static guint16 de_auth_fail_param ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 proto_item * item ;
 proto_tree * subtree ;
 item = proto_tree_add_item ( tree , hf_gsm_a_dtap_auts , tvb , offset , len , ENC_NA ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_dtap_elem [ DE_AUTH_FAIL_PARAM ] ) ;
 if ( len == 14 ) {
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_auts_sqn_ms_xor_ak , tvb , offset , 6 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_auts_mac_s , tvb , offset + 6 , 8 , ENC_NA ) ;
 }
 else expert_add_info ( pinfo , item , & ei_gsm_a_dtap_auts ) ;
 return ( len ) ;
 }