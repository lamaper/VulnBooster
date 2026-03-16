static int parse_CSortSet ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 guint32 count , i ;
 proto_item * item ;
 proto_tree * tree ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CSortSet , & item , txt ) ;
 count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cscortset_count , tvb , offset , 4 , count ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 offset = parse_padding ( tvb , offset , 4 , tree , "padding_sortArray[%u]" , i ) ;
 offset = parse_CSort ( tvb , offset , tree , pad_tree , "sortArray[%u]" , i ) ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }