static void dissect_rsvp_time_values ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_refresh_interval , tvb , offset2 , 4 , tvb_get_ntohl ( tvb , offset2 ) , "%u ms (%u seconds)" , tvb_get_ntohl ( tvb , offset2 ) , tvb_get_ntohl ( tvb , offset2 ) / 1000 ) ;
 proto_item_set_text ( ti , "TIME VALUES: %d ms" , tvb_get_ntohl ( tvb , offset2 ) ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_time_values_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }