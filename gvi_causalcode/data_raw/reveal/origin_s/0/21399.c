static int parse_UInt32Array ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , guint32 count , const char * item_name , const char * fmt , ... ) {
 guint32 v , i ;
 proto_tree * tree ;
 proto_item * item ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_Array , & item , txt ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 v = tvb_get_letohl ( tvb , offset ) ;
 proto_tree_add_uint_format ( tree , hf_mswsp_int32array_value , tvb , offset , 4 , v , "%s[%u] = %u" , item_name , i , v ) ;
 offset += 4 ;
 }
 proto_item_set_end ( item , tvb , offset ) ;
 return offset ;
 }