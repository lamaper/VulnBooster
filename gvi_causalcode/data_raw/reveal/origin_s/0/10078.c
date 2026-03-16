static int parse_lcid ( tvbuff_t * tvb , int offset , proto_tree * parent_tree , const char * text ) {
 proto_item * item ;
 proto_tree * tree ;
 guint32 lcid ;
 lcid = tvb_get_letohl ( tvb , offset ) ;
 item = proto_tree_add_uint_format ( parent_tree , hf_mswsp_lcid , tvb , offset , 4 , lcid , "%s: 0x%x" , text , lcid ) ;
 tree = proto_item_add_subtree ( item , ett_LCID ) ;
 proto_tree_add_uint ( tree , hf_mswsp_lcid_langid , tvb , offset + 2 , 2 , lcid ) ;
 proto_tree_add_uint ( tree , hf_mswsp_lcid_sortid , tvb , offset + 1 , 1 , ( lcid >> 16 ) & 0xF ) ;
 offset += 4 ;
 return offset ;
 }