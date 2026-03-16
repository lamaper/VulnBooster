proto_item * proto_tree_add_bytes_format_value ( proto_tree * tree , int hfindex , tvbuff_t * tvb , gint start , gint length , const guint8 * start_ptr , const char * format , ... ) {
 proto_item * pi ;
 va_list ap ;
 header_field_info * hfinfo ;
 gint item_length ;
 PROTO_REGISTRAR_GET_NTH ( hfindex , hfinfo ) ;
 get_hfi_length ( hfinfo , tvb , start , & length , & item_length ) ;
 test_length ( hfinfo , tvb , start , item_length ) ;
 CHECK_FOR_NULL_TREE ( tree ) ;
 TRY_TO_FAKE_THIS_ITEM ( tree , hfindex , hfinfo ) ;
 if ( start_ptr ) pi = proto_tree_add_bytes ( tree , hfindex , tvb , start , length , start_ptr ) ;
 else pi = proto_tree_add_bytes ( tree , hfindex , tvb , start , length , tvb_get_ptr ( tvb , start , length ) ) ;
 va_start ( ap , format ) ;
 proto_tree_set_representation_value ( pi , format , ap ) ;
 va_end ( ap ) ;
 return pi ;
 }