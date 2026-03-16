static void dissect_rsvp_notify_request ( proto_item * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 switch ( type ) {
 case 1 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - IPv4" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_notify_request_notify_node_address_ipv4 , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , ": Notify node: %s" , tvb_ip_to_str ( tvb , offset2 ) ) ;
 break ;
 }
 case 2 : {
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv6" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_notify_request_notify_node_address_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 proto_item_append_text ( ti , ": Notify node: %s" , tvb_ip6_to_str ( tvb , offset2 ) ) ;
 break ;
 }
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_notify_request_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }