static gint handle_message_field ( tvbuff_t * tvb , packet_info * pinfo , proto_item * header_tree , guint encoding , gint offset , guint8 * * signature , guint8 * signature_length ) {
 proto_tree * field_tree ;
 proto_item * item , * field_item ;
 guint8 field_code ;
 guint8 type_id ;
 gboolean is_reply_to = FALSE ;
 gint starting_offset = offset ;
 gint padding_start ;
 field_code = tvb_get_guint8 ( tvb , offset ) ;
 if ( HDR_REPLY_SERIAL == field_code ) {
 is_reply_to = TRUE ;
 }
 field_item = proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_field , tvb , offset , 1 , ENC_NA ) ;
 field_tree = proto_item_add_subtree ( field_item , ett_alljoyn_mess_header_field ) ;
 proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_header_fieldcode , tvb , offset , 1 , ENC_NA ) ;
 offset += 1 ;
 handle_message_header_expected_byte ( tvb , offset , field_tree , 0x01 ) ;
 offset += 1 ;
 item = proto_tree_add_item ( field_tree , hf_alljoyn_mess_body_header_typeid , tvb , offset , 1 , ENC_NA ) ;
 type_id = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 handle_message_header_expected_byte ( tvb , offset , field_tree , 0x00 ) ;
 offset += 1 ;
 offset = parse_arg ( tvb , pinfo , item , encoding , offset , field_tree , is_reply_to , type_id , field_code , signature , signature_length , starting_offset ) ;
 padding_start = offset ;
 offset = round_to_8byte ( offset , starting_offset ) ;
 add_padding_item ( padding_start , offset , tvb , field_tree ) ;
 if ( offset < 0 || offset > ( gint ) tvb_reported_length ( tvb ) ) {
 offset = ( gint ) tvb_reported_length ( tvb ) ;
 }
 proto_item_set_end ( field_tree , tvb , offset ) ;
 return offset ;
 }