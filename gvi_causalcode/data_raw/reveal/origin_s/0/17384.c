static void dissect_rsvp_association ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 guint16 association_type ;
 guint16 association_id ;
 proto_item_set_text ( ti , "ASSOCIATION " ) ;
 association_type = tvb_get_ntohs ( tvb , offset + 4 ) ;
 association_id = tvb_get_ntohs ( tvb , offset + 6 ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 (IPv4)" ) ;
 proto_item_append_text ( ti , "(IPv4): " ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_type , tvb , offset + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "%s. " , val_to_str ( association_type , association_type_vals , "Unknown (%u)" ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_id , tvb , offset + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "ID: %u. " , association_id ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_source_ipv4 , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Src: %s" , tvb_ip_to_str ( tvb , offset + 8 ) ) ;
 break ;
 case 2 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 (IPv6)" ) ;
 proto_item_append_text ( ti , "(IPv6): " ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_type , tvb , offset + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "%s. " , val_to_str ( association_type , association_type_vals , "Unknown (%u)" ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_id , tvb , offset + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "ID: %u. " , association_id ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_source_ipv6 , tvb , offset + 8 , 16 , ENC_NA ) ;
 proto_item_append_text ( ti , "Src: %s" , tvb_ip6_to_str ( tvb , offset + 8 ) ) ;
 break ;
 case 4 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 (Routing Area)" ) ;
 proto_item_append_text ( ti , "(Routing Area): " ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_type , tvb , offset + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "%s. " , val_to_str ( association_type , association_type_vals , "Unknown (%u)" ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_id , tvb , offset + 6 , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Association ID: %u, " , association_id ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_routing_area_id , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Routing Area ID: %u, " , tvb_get_ntohl ( tvb , offset + 8 ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_node_id , tvb , offset + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "Node ID: %s" , tvb_ip_to_str ( tvb , offset + 12 ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_padding , tvb , offset + 8 , 16 , ENC_NA ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_association_data , tvb , offset + 4 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }