guint16 de_bearer_cap_uplink ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string , int string_len ) {
 is_uplink = IS_UPLINK_TRUE ;
 return de_bearer_cap ( tvb , tree , pinfo , offset , len , add_string , string_len ) ;
 }