static guint16 de_u2u ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guint32 proto_discr ;
 proto_tree * subtree ;
 tvbuff_t * u2u_tvb ;
 curr_offset = offset ;
 proto_tree_add_item_ret_uint ( tree , hf_gsm_a_dtap_u2u_prot_discr , tvb , curr_offset , 1 , ENC_BIG_ENDIAN , & proto_discr ) ;
 curr_offset ++ ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , len - 1 , ett_gsm_dtap_elem [ DE_USER_USER ] , NULL , "User-user information" ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_data , tvb , curr_offset , len - 1 , ENC_NA ) ;
 u2u_tvb = tvb_new_subset_length ( tvb , curr_offset , len - 1 ) ;
 dissector_try_uint_new ( u2u_dissector_table , proto_discr , u2u_tvb , pinfo , proto_tree_get_root ( tree ) , TRUE , NULL ) ;
 return ( len ) ;
 }