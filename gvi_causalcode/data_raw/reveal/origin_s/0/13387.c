static void dissect_rsvp_lsp_attributes ( proto_tree * ti , packet_info * pinfo , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int tlv_off ;
 guint32 attributes ;
 guint16 tlv_type , tlv_len ;
 proto_tree * ti2 , * rsvp_lsp_attr_subtree ;
 if ( rsvp_class == RSVP_CLASS_LSP_REQUIRED_ATTRIBUTES ) proto_item_set_text ( ti , "LSP REQUIRED ATTRIBUTES: " ) ;
 else proto_item_set_text ( ti , "LSP ATTRIBUTES: " ) ;
 switch ( type ) {
 case 1 : proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type ) ;
 for ( tlv_off = 4 ;
 tlv_off < obj_length - 4 ;
 ) {
 tlv_type = tvb_get_ntohs ( tvb , offset + tlv_off ) ;
 tlv_len = tvb_get_ntohs ( tvb , offset + tlv_off + 2 ) ;
 if ( ( tlv_len == 0 ) || ( tlv_off + tlv_len > obj_length ) ) {
 proto_tree_add_expert ( rsvp_object_tree , pinfo , & ei_rsvp_invalid_length , tvb , offset + tlv_off + 2 , 2 ) ;
 return ;
 }
 switch ( tlv_type ) {
 case 1 : attributes = tvb_get_ntohl ( tvb , offset + tlv_off + 4 ) ;
 ti2 = proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_attributes_tlv , tvb , offset + tlv_off , 4 , ENC_BIG_ENDIAN ) ;
 rsvp_lsp_attr_subtree = proto_item_add_subtree ( ti2 , TREE ( TT_LSP_ATTRIBUTES_FLAGS ) ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_e2e , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_boundary , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_segment , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_integrity , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_contiguous , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_stitching , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_preplanned , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_nophp , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_oobmap , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_entropy , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_srlgcollect , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_costcollect , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_latcollect , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rsvp_lsp_attr_subtree , hf_rsvp_lsp_attr_latvarcollect , tvb , offset + tlv_off + 4 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( ti , "LSP Attribute:%s%s%s%s%s%s%s%s%s%s%s%s%s%s" , ( attributes & 0x00000001 ) ? " End-to-end re-routing" : "" , ( attributes & 0x00000002 ) ? " Boundary re-routing" : "" , ( attributes & 0x00000004 ) ? " Segment-based re-routing" : "" , ( attributes & 0x00000008 ) ? " LSP Integrity Required" : "" , ( attributes & 0x00000010 ) ? " Contiguous LSP" : "" , ( attributes & 0x00000020 ) ? " LSP stitching desired" : "" , ( attributes & 0x00000040 ) ? " Pre-Planned LSP Flag" : "" , ( attributes & 0x00000080 ) ? " Non-PHP behavior flag" : "" , ( attributes & 0x00000100 ) ? " OOB mapping flag" : "" , ( attributes & 0x00000200 ) ? " Entropy Label Capability" : "" , ( attributes & 0x00000400 ) ? " SRLG Collection Flag" : "" , ( attributes & 0x00000800 ) ? " Cost Collection Flag" : "" , ( attributes & 0x00001000 ) ? " Latency Collection Flag" : "" , ( attributes & 0x00002000 ) ? " Latency Variation Flag" : "" ) ;
 break ;
 default : proto_tree_add_uint_format ( rsvp_object_tree , hf_rsvp_type , tvb , offset + tlv_off , tlv_len , tlv_type , "Unknown TLV: %d" , tlv_type ) ;
 break ;
 }
 tlv_off += tlv_len ;
 }
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_lsp_attributes_tlv_data , tvb , offset + 4 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }