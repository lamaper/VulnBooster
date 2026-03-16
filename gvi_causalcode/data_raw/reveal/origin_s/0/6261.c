static gint handle_message_header_body ( tvbuff_t * tvb , packet_info * pinfo , gint offset , proto_item * message_tree , gboolean is_ardp ) {
 gint remaining_packet_length ;
 guint8 * signature ;
 guint8 signature_length = 0 ;
 proto_tree * header_tree , * flag_tree ;
 proto_item * header_item , * flag_item ;
 guint encoding ;
 gint packet_length_needed ;
 gint header_length = 0 , body_length = 0 ;
 remaining_packet_length = tvb_reported_length_remaining ( tvb , offset ) ;
 encoding = get_message_header_endianness ( tvb , offset ) ;
 if ( ENC_ALLJOYN_BAD_ENCODING == encoding ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Endian encoding '0x%0x'. Expected 'l' or 'B'" , tvb_get_guint8 ( tvb , offset + ENDIANNESS_OFFSET ) ) ;
 return offset + remaining_packet_length ;
 }
 if ( remaining_packet_length < MESSAGE_HEADER_LENGTH ) {
 if ( ! set_pinfo_desegment ( pinfo , offset , MESSAGE_HEADER_LENGTH - remaining_packet_length ) ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Remaining packet length is %d. Expected >= %d && <= %d" , remaining_packet_length , MESSAGE_HEADER_LENGTH , MAX_PACKET_LEN ) ;
 }
 return offset + remaining_packet_length ;
 }
 header_length = get_uint32 ( tvb , offset + HEADER_LENGTH_OFFSET , encoding ) ;
 body_length = get_uint32 ( tvb , offset + BODY_LENGTH_OFFSET , encoding ) ;
 packet_length_needed = ROUND_TO_8BYTE ( header_length ) + body_length + MESSAGE_HEADER_LENGTH ;
 if ( packet_length_needed > remaining_packet_length ) {
 if ( ! set_pinfo_desegment ( pinfo , offset , packet_length_needed - remaining_packet_length ) ) {
 if ( ! is_ardp ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "BAD DATA: Remaining packet length is %d. Expected %d" , remaining_packet_length , packet_length_needed ) ;
 return offset + remaining_packet_length ;
 }
 if ( remaining_packet_length < header_length ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "Fragmented ARDP message: Remaining packet length is %d. Expected %d" , remaining_packet_length , packet_length_needed ) ;
 return offset + remaining_packet_length ;
 }
 }
 else {
 return offset + remaining_packet_length ;
 }
 }
 header_item = proto_tree_add_item ( message_tree , hf_alljoyn_mess_header , tvb , offset , MESSAGE_HEADER_LENGTH , ENC_NA ) ;
 header_tree = proto_item_add_subtree ( header_item , ett_alljoyn_header ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_endian , tvb , offset + ENDIANNESS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_type , tvb , offset + TYPE_OFFSET , 1 , ENC_NA ) ;
 flag_item = proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_flags , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 flag_tree = proto_item_add_subtree ( flag_item , ett_alljoyn_header_flags ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_encrypted , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_compressed , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_global_broadcast , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_sessionless , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_allow_remote_msg , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_no_auto_start , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( flag_tree , hf_alljoyn_mess_header_flags_no_reply , tvb , offset + FLAGS_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_majorversion , tvb , offset + MAJORVERSION_OFFSET , 1 , ENC_NA ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_body_length , tvb , offset + BODY_LENGTH_OFFSET , 4 , encoding ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_serial , tvb , offset + SERIAL_OFFSET , 4 , encoding ) ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "Message %010u: '%s'" , get_uint32 ( tvb , offset + SERIAL_OFFSET , encoding ) , val_to_str_const ( tvb_get_guint8 ( tvb , offset + TYPE_OFFSET ) , message_header_encoding_vals , "Unexpected message type" ) ) ;
 proto_tree_add_item ( header_tree , hf_alljoyn_mess_header_header_length , tvb , offset + HEADER_LENGTH_OFFSET , 4 , encoding ) ;
 offset += MESSAGE_HEADER_LENGTH ;
 packet_length_needed -= MESSAGE_HEADER_LENGTH ;
 signature = handle_message_header_fields ( tvb , pinfo , message_tree , encoding , offset , header_length , & signature_length ) ;
 offset += ROUND_TO_8BYTE ( header_length ) ;
 packet_length_needed -= ROUND_TO_8BYTE ( header_length ) ;
 remaining_packet_length = tvb_reported_length_remaining ( tvb , offset ) ;
 if ( packet_length_needed > remaining_packet_length ) {
 col_append_sep_fstr ( pinfo -> cinfo , COL_INFO , NULL , "Fragmented ARDP message or bad data: Remaining packet length is %d. Expected %d" , remaining_packet_length , packet_length_needed ) ;
 return offset + remaining_packet_length ;
 }
 if ( body_length > 0 && signature != NULL && signature_length > 0 ) {
 offset = handle_message_body_parameters ( tvb , pinfo , message_tree , encoding , offset , body_length , signature , signature_length ) ;
 }
 return offset ;
 }