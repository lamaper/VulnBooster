static guint16 de_prio ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 curr_offset = offset ;
 proto_tree_add_item ( tree , hf_gsm_a_b8spare , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_call_prio , tvb , ( curr_offset << 3 ) + 5 , 3 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }