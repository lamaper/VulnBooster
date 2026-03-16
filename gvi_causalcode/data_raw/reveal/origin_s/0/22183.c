static gint handle_message_sasl ( tvbuff_t * tvb , packet_info * pinfo , gint offset , proto_tree * message_tree ) {
 gint return_value = offset ;
 const sasl_cmd * command ;
 command = find_sasl_command ( tvb , offset ) ;
 if ( command ) {
 gint newline_offset = tvb_find_guint8 ( tvb , offset + command -> length , - 1 , '\n' ) + 1 ;
 if ( 0 == newline_offset ) {
 if ( ( guint ) tvb_captured_length_remaining ( tvb , offset ) < MAX_SASL_PACKET_LENGTH && set_pinfo_desegment ( pinfo , offset , DESEGMENT_ONE_MORE_SEGMENT ) ) {
 return_value = offset + command -> length ;
 }
 else {
 return_value = 0 ;
 }
 return return_value ;
 }
 if ( newline_offset > 0 ) {
 gint length = command -> length ;
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "SASL-%s" , command -> text ) ;
 proto_tree_add_item ( message_tree , hf_alljoyn_sasl_command , tvb , offset , length , ENC_ASCII | ENC_NA ) ;
 offset += length ;
 length = newline_offset - offset ;
 proto_tree_add_item ( message_tree , hf_alljoyn_sasl_parameter , tvb , offset , length , ENC_ASCII | ENC_NA ) ;
 return_value = newline_offset ;
 }
 }
 return return_value ;
 }