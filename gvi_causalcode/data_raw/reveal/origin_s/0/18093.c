static void dissect_q931_segmented_message_ie ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree , proto_item * item ) {
 guint8 octet ;
 if ( len != 2 ) {
 expert_add_info_format ( pinfo , item , & ei_q931_invalid_length , "Segmented message: length is %d, should be 2" , len ) ;
 return ;
 }
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( octet & 0x80 ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_first_segment , tvb , offset , 1 , octet & 0x7F , "%u segments remaining" , octet & 0x7F ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_q931_not_first_segment , tvb , offset , 1 , octet & 0x7F , "%u segments remaining" , octet & 0x7F ) ;
 }
 proto_tree_add_item ( tree , hf_q931_segment_type , tvb , offset + 1 , 1 , ENC_BIG_ENDIAN ) ;
 }