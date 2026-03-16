static void dissect_rsvp_restart_cap ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 guint restart , recovery ;
 proto_item_set_text ( ti , "RESTART CAPABILITY: " ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 restart = tvb_get_ntohl ( tvb , offset2 ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_restart_cap_restart_time , tvb , offset2 , 4 , restart , "%d ms" , restart ) ;
 recovery = tvb_get_ntohl ( tvb , offset2 + 4 ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_restart_cap_recovery_time , tvb , offset2 + 4 , 4 , recovery , "%d ms" , recovery ) ;
 proto_item_append_text ( ti , "Restart Time: %d ms. Recovery Time: %d ms." , restart , recovery ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_restart_cap_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }