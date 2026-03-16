void proto_item_set_end ( proto_item * pi , tvbuff_t * tvb , gint end ) {
 field_info * fi ;
 TRY_TO_FAKE_THIS_REPR_VOID ( pi ) ;
 fi = PITEM_FINFO ( pi ) ;
 if ( fi == NULL ) return ;
 end += tvb_raw_offset ( tvb ) ;
 DISSECTOR_ASSERT ( end >= fi -> start ) ;
 fi -> length = end - fi -> start ;
 }