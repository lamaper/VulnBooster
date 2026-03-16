static guint16 de_auth_param_rand ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_rand , tvb , offset , 16 , ENC_NA ) ;
 return ( 16 ) ;
 }