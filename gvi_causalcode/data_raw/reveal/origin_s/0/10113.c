static guint16 de_keypad_facility ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len _U_ , gchar * add_string , int string_len ) {
 guint8 keypad_char ;
 guint32 curr_offset ;
 proto_item * item ;
 curr_offset = offset ;
 keypad_char = tvb_get_guint8 ( tvb , curr_offset ) & 0x7f ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , curr_offset << 3 , 1 , ENC_BIG_ENDIAN ) ;
 item = proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_keypad_information , tvb , curr_offset , 1 , keypad_char , "%c" , keypad_char ) ;
 if ( ( ( keypad_char < '0' ) || ( keypad_char > '9' ) ) && ( ( keypad_char < 'A' ) || ( keypad_char > 'D' ) ) && ( keypad_char != '*' ) && ( keypad_char != '#' ) ) expert_add_info ( pinfo , item , & ei_gsm_a_dtap_keypad_info_not_dtmf_digit ) ;
 curr_offset ++ ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - %c" , keypad_char ) ;
 return ( curr_offset - offset ) ;
 }