static guint16 de_ciph_key_seq_num ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset , bit_offset ;
 curr_offset = offset ;
 if ( RIGHT_NIBBLE == len ) bit_offset = 4 ;
 else bit_offset = 0 ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + bit_offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_key_seq , tvb , ( curr_offset << 3 ) + bit_offset + 1 , 3 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }