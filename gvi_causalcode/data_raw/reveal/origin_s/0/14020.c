int parse_CColumnGroup ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree _U_ , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item , * ti ;
 va_list ap ;
 const char * txt ;
 guint32 count , groupPid , i ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_CColumnGroup , & item , txt ) ;
 count = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint ( tree , hf_mswsp_ccolumngroup_count , tvb , offset , 4 , count ) ;
 offset += 4 ;
 groupPid = tvb_get_letohl ( tvb , offset ) ;
 ti = proto_tree_add_uint ( tree , hf_mswsp_ccolumngroup_grouppid , tvb , offset , 4 , groupPid ) ;
 if ( ( 0xFFFF0000 & groupPid ) == 0x7FFF0000 ) {
 proto_item_append_text ( ti , " Idx: %u" , groupPid & 0xFFFF ) ;
 }
 else {
 proto_item_append_text ( ti , "<Invalid>" ) ;
 }
 offset += 4 ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 guint32 pid , weight ;
 pid = tvb_get_letohl ( tvb , offset ) ;
 weight = tvb_get_letohl ( tvb , offset + 4 ) ;
 proto_tree_add_uint_format ( tree , hf_mswsp_ccolumngroup_pid , tvb , offset , 8 , pid , "Props[%u]: pid: %u weight: %u" , i , pid , weight ) ;
 offset += 8 ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }