static void dissect_rsvp_style ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 switch ( type ) {
 case 1 : {
 guint32 style ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_style_flags , tvb , offset2 , 1 , ENC_BIG_ENDIAN ) ;
 style = tvb_get_ntoh24 ( tvb , offset2 + 1 ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_style_style , tvb , offset2 + 1 , 3 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "STYLE: %s (%d)" , val_to_str_const ( style , style_vals , "Unknown" ) , style ) ;
 break ;
 }
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_style_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }