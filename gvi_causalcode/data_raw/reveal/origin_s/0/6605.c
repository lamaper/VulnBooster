static int parse_CAggregSet ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree , const char * fmt , ... ) {
 guint32 cCount , i ;
 proto_item * item ;
 proto_tree * tree ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CAggregSet , & item , txt ) ;
 cCount = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_caggregset_count , tvb , offset , 4 , cCount ) ;
 offset += 4 ;
 for ( i = 0 ;
 i < cCount ;
 i ++ ) {
 offset = parse_CAggregSpec ( tvb , offset , tree , pad_tree , "AggregSpecs[%u]" , i ) ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }