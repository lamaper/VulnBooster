static int parse_CRowSeekNext ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CRowsSeekNext , & item , txt ) ;
 proto_tree_add_item ( tree , hf_mswsp_crowseeknext_cskip , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }