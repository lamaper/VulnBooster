static guint16 de_ms_net_feat_sup ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset , bit_offset ;
 curr_offset = offset ;
 bit_offset = ( curr_offset << 3 ) + 4 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , bit_offset , 3 , ENC_BIG_ENDIAN ) ;
 bit_offset += 3 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_ext_periodic_timers , tvb , bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }