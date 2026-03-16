static int parse_CContentRestriction ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , struct CContentRestriction * v , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 va_list ap ;
 guint32 cc ;
 const char * txt ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CContentRestriction , & item , txt ) ;
 offset = parse_CFullPropSpec ( tvb , offset , tree , pad_tree , & v -> property , "Property" ) ;
 offset = parse_padding ( tvb , offset , 4 , pad_tree , "Padding1" ) ;
 cc = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_ccontentrestrict_cc , tvb , offset , 4 , cc ) ;
 offset += 4 ;
 proto_tree_add_item_ret_string ( tree , hf_mswsp_ccontentrestrict_phrase , tvb , offset , 2 * cc , ENC_LITTLE_ENDIAN | ENC_UCS_2 , wmem_packet_scope ( ) , & v -> phrase ) ;
 offset += 2 * cc ;
 offset = parse_padding ( tvb , offset , 4 , pad_tree , "Padding2" ) ;
 v -> lcid = tvb_get_letohl ( tvb , offset ) ;
 offset = parse_lcid ( tvb , offset , tree , "lcid" ) ;
 v -> method = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_ccontentrestrict_method , tvb , offset , 4 , v -> method ) ;
 offset += 4 ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }