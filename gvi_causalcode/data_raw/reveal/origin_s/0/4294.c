static void dissect_rsvp_diffserv_aware_te ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 proto_item * hidden_item ;
 int offset2 = offset + 4 ;
 guint8 ct = 0 ;
 hidden_item = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_DSTE ] , tvb , offset , 8 , ENC_NA ) ;
 PROTO_ITEM_SET_HIDDEN ( hidden_item ) ;
 switch ( type ) {
 case 1 : ct = tvb_get_guint8 ( tvb , offset2 + 3 ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_DSTE_CLASSTYPE ] , tvb , offset2 + 3 , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "CLASSTYPE: CT %u" , ct ) ;
 break ;
 default : proto_item_set_text ( ti , "CLASSTYPE: (Unknown C-type)" ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_diffserv_aware_te_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }