static int parse_CReuseWhere ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , proto_tree * pad_tree _U_ , struct CReuseWhere * v , const char * fmt , ... ) {
 proto_item * item ;
 va_list ap ;
 const char * txt ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_mswsp_msg_creusewhere , & item , txt ) ;
 v -> whereId = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 proto_item_append_text ( item , " Id: %u" , v -> whereId ) ;
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }