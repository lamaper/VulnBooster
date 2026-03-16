static int parse_uin32_array ( tvbuff_t * tvb , int offset , proto_tree * tree , guint32 count , const char * fmt , ... ) {
 guint32 v , i ;
 proto_item * item ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 proto_tree_add_subtree ( tree , tvb , offset , count * 4 , ett_mswsp_uin32_array , & item , txt ) ;
 proto_item_append_text ( item , " count %u [" , count ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 v = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 if ( i > 0 ) {
 proto_item_append_text ( item , ",%u" , v ) ;
 }
 else {
 proto_item_append_text ( item , "%u" , v ) ;
 }
 }
 proto_item_append_text ( item , "]" ) ;
 return offset ;
 }