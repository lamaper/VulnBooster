static int parse_CRowSeekByBookmark ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 guint32 num ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CRowsSeekByBookmark , & item , txt ) ;
 num = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_mswsp_crowseekbybookmark_cbookmarks , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = parse_UInt32Array ( tvb , offset , tree , num , "abookmark" , "abookmarks" ) ;
 num = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_item ( tree , hf_mswsp_crowseekbybookmark_maxret , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 offset = parse_UInt32Array ( tvb , offset , tree , num , "ascret" , "ascret" ) ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }