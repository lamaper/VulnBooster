static void dissect_rsvp_hop ( proto_item * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int offset2 = offset + 4 ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - IPv4" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_neighbor_address_ipv4 , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_logical_interface , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "HOP: IPv4, %s" , tvb_ip_to_str ( tvb , offset2 ) ) ;
 break ;
 case 2 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv6" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_neighbor_address_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_logical_interface , tvb , offset2 + 16 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 3 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "3 - IPv4 IF-ID" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_neighbor_address_ipv4 , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_logical_interface , tvb , offset2 + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "HOP: IPv4 IF-ID. Control IPv4: %s. " , tvb_ip_to_str ( tvb , offset2 ) ) ;
 dissect_rsvp_ifid_tlv ( ti , pinfo , rsvp_object_tree , tvb , offset + 12 , obj_length - 12 , TREE ( TT_HOP_SUBOBJ ) ) ;
 break ;
 case 4 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 - IPv6 IF-ID" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_neighbor_address_ipv6 , tvb , offset2 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_logical_interface , tvb , offset2 + 16 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "HOP: IPv6 IF-ID. Control IPv6: %s. " , tvb_ip6_to_str ( tvb , offset2 ) ) ;
 dissect_rsvp_ifid_tlv ( ti , pinfo , rsvp_object_tree , tvb , offset + 24 , obj_length - 24 , TREE ( TT_HOP_SUBOBJ ) ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_hop_data , tvb , offset2 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }