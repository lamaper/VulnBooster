static void dissect_rsvp_lsp_tunnel_if_id_tlv ( proto_tree * rsvp_object_tree , packet_info * pinfo , tvbuff_t * tvb , int offset , int tlv_length , int subtree_type ) {
 int tlv_off ;
 guint16 tlv_type ;
 int tlv_len ;
 proto_tree * ti , * rsvp_lsp_tunnel_if_id_subtree ;
 for ( tlv_off = 0 ;
 tlv_off < tlv_length ;
 ) {
 tlv_type = tvb_get_ntohs ( tvb , offset + tlv_off ) ;
 tlv_len = tvb_get_ntohs ( tvb , offset + tlv_off + 2 ) ;
 if ( ( tlv_len == 0 ) || ( ( tlv_off + tlv_len ) > tlv_length ) ) {
 proto_tree_add_expert ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset + tlv_off + 2 , 2 ) ;
 return ;
 }
 switch ( tlv_type ) {
 case 1 : rsvp_lsp_tunnel_if_id_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , NULL , "Unnumbered component link identifier: %u" , tvb_get_ntohl ( tvb , offset + tlv_off + 4 ) ) ;
 proto_tree_add_uint_format_value ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "1 (Unnumbered component link identifier)" ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_component_link_identifier , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 2 : rsvp_lsp_tunnel_if_id_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , NULL , "IPv4 component link identifier: %s" , tvb_ip_to_str ( tvb , offset + tlv_off + 4 ) ) ;
 proto_tree_add_uint_format_value ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "2 (IPv4 component link identifier)" ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_component_link_identifier_ipv4 , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 break ;
 case 32769 : rsvp_lsp_tunnel_if_id_subtree = proto_tree_add_subtree_format ( rsvp_object_tree , tvb , offset + tlv_off , tlv_len , subtree_type , & ti , "Targeted client layer: " ) ;
 proto_tree_add_uint_format_value ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "32769 (Targeted client layer)" ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_length , tvb , offset + tlv_off + 2 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_lsp_encoding_type , tvb , offset + tlv_off + 4 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_switching_type , tvb , offset + tlv_off + 5 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_signal_type , tvb , offset + tlv_off + 6 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_connection_id , tvb , offset + tlv_off + 8 , 8 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_sc_pc_id , tvb , offset + tlv_off + 16 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_tunnel_if_id_subtree , hf_rsvp_lsp_tunnel_if_id_sc_pc_scn_address , tvb , offset + tlv_off + 20 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "LSP Encoding=%s, Switching Type=%s, Signal Type=%s" , rval_to_str ( tvb_get_guint8 ( tvb , offset + tlv_off + 4 ) , gmpls_lsp_enc_rvals , "Unknown (%d)" ) , rval_to_str ( tvb_get_guint8 ( tvb , offset + tlv_off + 5 ) , gmpls_switching_type_rvals , "Unknown (%d)" ) , val_to_str_ext ( tvb_get_guint8 ( tvb , offset + tlv_off + 6 ) , & gmpls_sonet_signal_type_str_ext , "Unknown (%d)" ) ) ;
 break ;
 default : proto_tree_add_uint_format ( rsvp_object_tree , hf_rsvp_type , tvb , offset + tlv_off , 2 , tlv_type , "Unknown TLV: %u" , tlv_type ) ;
 break ;
 }
 tlv_off += tlv_len ;
 }
 }