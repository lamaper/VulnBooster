proto_item * proto_tree_add_item_new_ret_length ( proto_tree * tree , header_field_info * hfinfo , tvbuff_t * tvb , const gint start , gint length , const guint encoding , gint * lenretval ) {
 field_info * new_fi ;
 gint item_length ;
 proto_item * item ;
 DISSECTOR_ASSERT_HINT ( hfinfo != NULL , "Not passed hfi!" ) ;
 get_hfi_length ( hfinfo , tvb , start , & length , & item_length ) ;
 test_length ( hfinfo , tvb , start , item_length ) ;
 if ( ! tree ) {
 * lenretval = get_full_length ( hfinfo , tvb , start , length , item_length , encoding ) ;
 return NULL ;
 }
 TRY_TO_FAKE_THIS_ITEM ( tree , hfinfo -> id , hfinfo ) ;
 new_fi = new_field_info ( tree , hfinfo , tvb , start , item_length ) ;
 item = proto_tree_new_item ( new_fi , tree , tvb , start , length , encoding ) ;
 * lenretval = new_fi -> length ;
 return item ;
 }