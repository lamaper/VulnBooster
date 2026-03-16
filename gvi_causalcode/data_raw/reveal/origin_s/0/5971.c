void proto_item_set_len ( proto_item * pi , const gint length ) {
 field_info * fi ;
 TRY_TO_FAKE_THIS_REPR_VOID ( pi ) ;
 fi = PITEM_FINFO ( pi ) ;
 if ( fi == NULL ) return ;
 DISSECTOR_ASSERT ( length >= 0 ) ;
 fi -> length = length ;
 if ( fi -> value . ftype -> ftype == FT_BYTES && length <= ( gint ) fi -> value . value . bytes -> len ) fi -> value . value . bytes -> len = length ;
 }