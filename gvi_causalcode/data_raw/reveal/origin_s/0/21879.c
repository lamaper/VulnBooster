int parse_CPidMapper ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 proto_item * item ;
 proto_tree * tree ;
 va_list ap ;
 guint32 count , i ;
 const char * txt ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CPidMapper , & item , txt ) ;
 count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cpidmapper_count , tvb , offset , 4 , count ) ;
 offset += 4 ;
 offset = parse_padding ( tvb , offset , 8 , pad_tree , "CPidMapper_PropSpec" ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 struct CFullPropSpec v ;
 ZERO_STRUCT ( v ) ;
 offset = parse_padding ( tvb , offset , 4 , pad_tree , "CPidMapper_PropSpec[%u]" , i ) ;
 offset = parse_CFullPropSpec ( tvb , offset , tree , pad_tree , & v , "PropSpec[%u]" , i ) ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }