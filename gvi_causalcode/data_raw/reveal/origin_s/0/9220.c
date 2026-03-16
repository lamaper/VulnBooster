static void dissect_rsvp_lsp_tunnel_if_id ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 proto_item_set_text ( ti , "LSP INTERFACE-ID: " ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 - Unnumbered interface" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_router_id , tvb , offset + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_interface_id , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LSP INTERFACE-ID: Unnumbered, Router-ID %s, Interface-ID %d" , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohl ( tvb , offset + 8 ) ) ;
 break ;
 case 2 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 - IPv4" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_ipv4_interface_address , tvb , offset + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_target_igp_instance , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LSP INTERFACE-ID: IPv4, interface address %s," "IGP instance %s" , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_ip_to_str ( tvb , offset + 8 ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_action , tvb , offset + 12 , 1 , ENC_BIG_ENDIAN ) ;
 dissect_rsvp_lsp_tunnel_if_id_tlv ( rsvp_object_tree , pinfo , tvb , offset + 16 , obj_length - 16 , TREE ( TT_LSP_TUNNEL_IF_ID_SUBTREE ) ) ;
 break ;
 case 3 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "3 - IPv6" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_ipv6_interface_address , tvb , offset + 4 , 16 , ENC_NA ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_target_igp_instance , tvb , offset + 20 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LSP INTERFACE-ID: IPv6, interface address %s," "IGP instance %s" , tvb_ip6_to_str ( tvb , offset + 4 ) , tvb_ip_to_str ( tvb , offset + 20 ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_action , tvb , offset + 24 , 1 , ENC_BIG_ENDIAN ) ;
 dissect_rsvp_lsp_tunnel_if_id_tlv ( rsvp_object_tree , pinfo , tvb , offset + 28 , obj_length - 28 , TREE ( TT_LSP_TUNNEL_IF_ID_SUBTREE ) ) ;
 break ;
 case 4 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 - Unnumbered interface with target" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_router_id , tvb , offset + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_interface_id , tvb , offset + 8 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_target_igp_instance , tvb , offset + 12 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "LSP INTERFACE-ID: Unnumbered with target, Router-ID %s," " Interface-ID %d, IGP instance %s" , tvb_ip_to_str ( tvb , offset + 4 ) , tvb_get_ntohl ( tvb , offset + 8 ) , tvb_ip_to_str ( tvb , offset + 12 ) ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_action , tvb , offset + 16 , 1 , ENC_BIG_ENDIAN ) ;
 dissect_rsvp_lsp_tunnel_if_id_tlv ( rsvp_object_tree , pinfo , tvb , offset + 20 , obj_length - 20 , TREE ( TT_LSP_TUNNEL_IF_ID_SUBTREE ) ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_tunnel_if_id_data , tvb , offset + 4 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }