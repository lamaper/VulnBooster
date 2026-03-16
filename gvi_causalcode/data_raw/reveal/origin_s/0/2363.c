static void dissect_rsvp_detour ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int remaining_length , count ;
 int iter ;
 proto_item_set_text ( ti , "DETOUR: " ) ;
 switch ( type ) {
 case 7 : iter = 0 ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 for ( remaining_length = obj_length - 4 , count = 1 ;
 remaining_length > 0 ;
 remaining_length -= 8 , count ++ ) {
 if ( remaining_length < 8 ) {
 proto_tree_add_expert_format ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset + remaining_length , obj_length - remaining_length , "Invalid length: cannot decode" ) ;
 proto_item_append_text ( ti , "Invalid length" ) ;
 break ;
 }
 iter ++ ;
 proto_tree_add_ipv4_format ( rsvp_object_tree , hf_rsvp_detour_plr_id , tvb , offset + ( 4 * iter ) , 4 , tvb_get_ntohl ( tvb , offset + ( 4 * iter ) ) , "PLR ID %d: %s" , count , tvb_ip_to_str ( tvb , offset + ( 4 * iter ) ) ) ;
 iter ++ ;
 proto_tree_add_ipv4_format ( rsvp_object_tree , hf_rsvp_detour_avoid_node_id , tvb , offset + ( 4 * iter ) , 4 , tvb_get_ntohl ( tvb , offset + ( 4 * iter ) ) , "Avoid Node ID %d: %s" , count , tvb_ip_to_str ( tvb , offset + ( 4 * iter ) ) ) ;
 }
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_detour_data , tvb , offset + 4 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }