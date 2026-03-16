static int parse_padding ( tvbuff_t * tvb , int offset , int alignment , proto_tree * pad_tree , const char * fmt , ... ) {
 if ( offset % alignment ) {
 const int padding = alignment - ( offset % alignment ) ;
 const char * txt ;
 va_list ap ;
 proto_item * ti ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 proto_tree_add_subtree ( pad_tree , tvb , offset , padding , ett_mswsp_msg_padding , & ti , txt ) ;
 va_end ( ap ) ;
 proto_item_append_text ( ti , " (%d)" , padding ) ;
 offset += padding ;
 }
 DISSECTOR_ASSERT ( ( offset % alignment ) == 0 ) ;
 return offset ;
 }