static int parse_CSort ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree _U_ , const char * fmt , ... ) {
 guint32 col , ord , ind ;
 proto_item * item ;
 proto_tree * tree ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CSort , & item , txt ) ;
 col = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cscort_column , tvb , offset , 4 , col ) ;
 offset += 4 ;
 ord = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cscort_order , tvb , offset , 4 , ord ) ;
 offset += 4 ;
 ind = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_cscort_individual , tvb , offset , 4 , ind ) ;
 offset += 4 ;
 offset = parse_lcid ( tvb , offset , tree , "lcid" ) ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }