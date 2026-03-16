static int parse_CRowSeekAt ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 va_list ap ;
 const char * txt ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CRowsSeekAt , & item , txt ) ;
 proto_tree_add_item ( tree , hf_mswsp_crowseekat_bmkoffset , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowseekat_skip , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowseekat_hregion , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }