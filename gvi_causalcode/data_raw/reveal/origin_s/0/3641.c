static void dissect_rsvp_message_id_list ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 int mylen ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_list_flags , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_list_epoch , tvb , offset + 5 , 3 , ENC_BIG_ENDIAN ) ;
 for ( mylen = 8 ;
 mylen < obj_length ;
 mylen += 4 ) proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_list_message_id , tvb , offset + mylen , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "MESSAGE-ID LIST: %d IDs" , ( obj_length - 8 ) / 4 ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_message_id_list_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }