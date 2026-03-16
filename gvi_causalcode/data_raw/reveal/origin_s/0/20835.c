static guint16 de_llc ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 dissect_q931_bearer_capability_ie ( tvb , offset , len , tree ) ;
 curr_offset = curr_offset + len ;
 return ( curr_offset - offset ) ;
 }