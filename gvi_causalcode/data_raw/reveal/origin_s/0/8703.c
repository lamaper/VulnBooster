void tvb_composite_append ( tvbuff_t * tvb , tvbuff_t * member ) {
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 tvb_comp_t * composite ;
 DISSECTOR_ASSERT ( tvb && ! tvb -> initialized ) ;
 DISSECTOR_ASSERT ( tvb -> ops == & tvb_composite_ops ) ;
 DISSECTOR_ASSERT ( member -> length ) ;
 composite = & composite_tvb -> composite ;
 composite -> tvbs = g_slist_append ( composite -> tvbs , member ) ;
 }