static int parse_CAggregSortKey ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 guint32 order ;
 proto_item * item ;
 proto_tree * tree ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CAggregSortKey , & item , txt ) ;
 order = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_caggregsortkey_order , tvb , offset , 4 , order ) ;
 offset += 4 ;
 offset = parse_CAggregSpec ( tvb , offset , tree , pad_tree , "ColumnSpec" ) ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }