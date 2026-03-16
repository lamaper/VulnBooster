static int dissect_q931_guint16_value ( tvbuff_t * tvb , packet_info * pinfo , int offset , int len , proto_tree * tree , proto_item * item , int hf_value ) {
 guint8 octet ;
 guint16 value ;
 int value_len ;
 value_len = 0 ;
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( octet & Q931_IE_VL_EXTENSION ) {
 goto bad_length ;
 }
 value = ( octet & 0x3 ) << 14 ;
 offset += 1 ;
 len -= 1 ;
 value_len ++ ;
 if ( len == 0 ) {
 goto past_end ;
 }
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( octet & Q931_IE_VL_EXTENSION ) {
 goto bad_length ;
 }
 value |= ( octet & 0x7F ) << 7 ;
 offset += 1 ;
 len -= 1 ;
 value_len ++ ;
 if ( len == 0 ) {
 goto past_end ;
 }
 octet = tvb_get_guint8 ( tvb , offset ) ;
 if ( ! ( octet & Q931_IE_VL_EXTENSION ) ) {
 goto bad_length ;
 }
 value |= ( octet & 0x7F ) ;
 offset += 1 ;
 value_len ++ ;
 proto_tree_add_uint_format_value ( tree , hf_value , tvb , offset , value_len , value , "%u ms" , value ) ;
 return value_len ;
 past_end : expert_add_info_format ( pinfo , item , & ei_q931_invalid_length , "%s goes past end of information element" , proto_registrar_get_name ( hf_value ) ) ;
 return - 1 ;
 bad_length : expert_add_info_format ( pinfo , item , & ei_q931_invalid_length , "%s isn't 3 octets long" , proto_registrar_get_name ( hf_value ) ) ;
 return - 1 ;
 }