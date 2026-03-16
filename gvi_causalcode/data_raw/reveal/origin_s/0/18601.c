static void dissect_rsvp_label_set ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 8 ;
 guint8 label_type ;
 int len , i ;
 len = obj_length - 8 ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_set_action , tvb , offset + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , ": %s" , val_to_str ( tvb_get_guint8 ( tvb , offset + 4 ) , action_type_vals , "Unknown (%u)" ) ) ;
 label_type = tvb_get_guint8 ( tvb , offset + 7 ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_label_set_type , tvb , offset + 7 , 1 , label_type , "%s" , ( label_type == 1 ) ? "Packet Label" : "Generalized Label" ) ;
 proto_item_append_text ( ti , ", %s" , ( label_type == 1 ) ? "Packet Label: " : "Generalized Label: " ) ;
 for ( i = 0 ;
 i < len / 4 ;
 i ++ ) {
 guint32 subchannel = tvb_get_ntohl ( tvb , offset2 + i * 4 ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_label_set_subchannel , tvb , offset2 + i * 4 , 4 , subchannel , "Subchannel %u: %u (0x%x)" , i + 1 , subchannel , subchannel ) ;
 if ( i < 5 ) {
 if ( i != 0 ) proto_item_append_text ( ti , ", " ) ;
 proto_item_append_text ( ti , "%u" , tvb_get_ntohl ( tvb , offset2 + i * 4 ) ) ;
 }
 }
 }