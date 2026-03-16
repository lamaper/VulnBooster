static void handle_message_header_expected_byte ( tvbuff_t * tvb , gint offset , proto_tree * field_tree , guint8 expected_value ) {
 proto_item * item ;
 guint8 byte_value ;
 item = proto_tree_add_item ( field_tree , hf_alljoyn_uint8 , tvb , offset , 1 , ENC_NA ) ;
 byte_value = tvb_get_guint8 ( tvb , offset ) ;
 if ( expected_value == byte_value ) {
 proto_item_set_text ( item , "0x%02x byte" , expected_value ) ;
 }
 else {
 proto_item_set_text ( item , "Expected '0x%02x byte' but found '0x%02x'" , expected_value , byte_value ) ;
 }
 }