static guint16 de_auth_resp_param ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_sres , tvb , offset , 4 , ENC_NA ) ;
 return ( 4 ) ;
 }