static guint16 de_auth_param_autn ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 proto_item * item ;
 proto_tree * subtree ;
 item = proto_tree_add_item ( tree , hf_gsm_a_dtap_autn , tvb , offset , len , ENC_NA ) ;
 subtree = proto_item_add_subtree ( item , ett_gsm_dtap_elem [ DE_AUTH_PARAM_AUTN ] ) ;
 if ( len == 16 ) {
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_autn_sqn_xor_ak , tvb , offset , 6 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_autn_amf , tvb , offset + 6 , 2 , ENC_NA ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_autn_mac , tvb , offset + 8 , 8 , ENC_NA ) ;
 }
 else expert_add_info ( pinfo , item , & ei_gsm_a_dtap_autn ) ;
 return ( len ) ;
 }