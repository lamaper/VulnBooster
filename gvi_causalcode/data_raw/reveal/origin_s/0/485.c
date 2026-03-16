int parse_CRowsetProperties ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree _U_ , const char * fmt , ... ) {
 proto_item * item ;
 proto_tree * tree ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CRowsetProperties , & item , txt ) ;
 proto_tree_add_bitmask_with_flags ( tree , tvb , offset , hf_mswsp_bool_options , ett_mswsp_bool_options , mswsp_bool_options , ENC_LITTLE_ENDIAN , BMT_NO_APPEND ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowsetprops_ulmaxopenrows , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowsetprops_ulmemusage , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowsetprops_cmaxresults , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_tree_add_item ( tree , hf_mswsp_crowsetprops_ccmdtimeout , tvb , offset , 4 , ENC_LITTLE_ENDIAN ) ;
 offset += 4 ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }