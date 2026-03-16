proto_item * proto_tree_add_uint64 ( proto_tree * tree , int hfindex , tvbuff_t * tvb , gint start , gint length , guint64 value ) {
 proto_item * pi = NULL ;
 header_field_info * hfinfo ;
 CHECK_FOR_NULL_TREE ( tree ) ;
 TRY_TO_FAKE_THIS_ITEM ( tree , hfindex , hfinfo ) ;
 switch ( hfinfo -> type ) {
 case FT_UINT40 : case FT_UINT48 : case FT_UINT56 : case FT_UINT64 : case FT_FRAMENUM : pi = proto_tree_add_pi ( tree , hfinfo , tvb , start , & length ) ;
 proto_tree_set_uint64 ( PNODE_FINFO ( pi ) , value ) ;
 break ;
 default : DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }
 return pi ;
 }