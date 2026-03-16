int parse_CColumnSet ( tvbuff_t * tvb , int offset , proto_tree * tree , const char * fmt , ... ) {
 guint32 count , v , i ;
 proto_item * item ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 count = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 proto_tree_add_subtree ( tree , tvb , offset , count * 4 , ett_mswsp_uin32_array , & item , txt ) ;
 proto_item_append_text ( item , " Count %u [" , count ) ;
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