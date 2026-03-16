static int parse_CAggregSpec ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 proto_item * item ;
 proto_tree * tree ;
 va_list ap ;
 guint8 type ;
 guint32 ccAlias , idColumn ;
 const char * txt ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CAggregSpec , & item , txt ) ;
 type = tvb_get_guint8 ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_caggregspec_type , tvb , offset , 1 , type ) ;
 proto_item_append_text ( item , "type: %u" , type ) ;
 offset += 1 ;
 offset = parse_padding ( tvb , offset , 4 , pad_tree , "padding" ) ;
 ccAlias = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_caggregspec_ccalias , tvb , offset , 1 , ccAlias ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_caggregspec_alias , tvb , offset , 2 * ccAlias , ENC_LITTLE_ENDIAN | ENC_UCS_2 ) ;
 offset += 2 * ccAlias ;
 idColumn = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_caggregspec_idcolumn , tvb , offset , 1 , idColumn ) ;
 offset += 4 ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }