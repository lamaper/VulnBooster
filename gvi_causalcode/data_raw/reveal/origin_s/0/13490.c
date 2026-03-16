static guint16 de_auth_resp_param_ext ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_xres , tvb , offset , len , ENC_NA ) ;
 return ( len ) ;
 }