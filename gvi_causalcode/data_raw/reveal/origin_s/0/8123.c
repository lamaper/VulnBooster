static void dissect_rsvp_message_id_ack ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_flags , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_epoch , tvb , offset + 5 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_message_id , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "MESSAGE-ID ACK: %d" , tvb_get_ntohl ( tvb , offset + 8 ) ) ;
 break ;
 case 2 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_flags , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_epoch , tvb , offset + 5 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_message_id , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "MESSAGE-ID NACK: %d" , tvb_get_ntohl ( tvb , offset + 8 ) ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_ack_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }