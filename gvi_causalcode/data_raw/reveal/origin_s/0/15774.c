int parse_CColumnGroupArray ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 va_list ap ;
 const char * txt ;
 guint32 count , i ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CColumnGroupArray , & item , txt ) ;
 count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_ccolumngrouparray_count , tvb , offset , 4 , count ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 offset = parse_padding ( tvb , offset , 4 , pad_tree , "aGroupArray[%u]" , i ) ;
 offset = parse_CColumnGroup ( tvb , offset , tree , pad_tree , "aGroupArray[%u]" , i ) ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }