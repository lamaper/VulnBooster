void tvb_composite_finalize ( tvbuff_t * tvb ) {
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 GSList * slist ;
 guint num_members ;
 tvbuff_t * member_tvb ;
 tvb_comp_t * composite ;
 int i = 0 ;
 DISSECTOR_ASSERT ( tvb && ! tvb -> initialized ) ;
 DISSECTOR_ASSERT ( tvb -> ops == & tvb_composite_ops ) ;
 DISSECTOR_ASSERT ( tvb -> length == 0 ) ;
 DISSECTOR_ASSERT ( tvb -> reported_length == 0 ) ;
 composite = & composite_tvb -> composite ;
 num_members = g_slist_length ( composite -> tvbs ) ;
 DISSECTOR_ASSERT ( num_members ) ;
 composite -> start_offsets = g_new ( guint , num_members ) ;
 composite -> end_offsets = g_new ( guint , num_members ) ;
 for ( slist = composite -> tvbs ;
 slist != NULL ;
 slist = slist -> next ) {
 DISSECTOR_ASSERT ( ( guint ) i < num_members ) ;
 member_tvb = ( tvbuff_t * ) slist -> data ;
 composite -> start_offsets [ i ] = tvb -> length ;
 tvb -> length += member_tvb -> length ;
 tvb -> reported_length += member_tvb -> reported_length ;
 composite -> end_offsets [ i ] = tvb -> length - 1 ;
 i ++ ;
 }
 DISSECTOR_ASSERT ( composite -> tvbs ) ;
 tvb_add_to_chain ( ( tvbuff_t * ) composite -> tvbs -> data , tvb ) ;
 tvb -> initialized = TRUE ;
 tvb -> ds_tvb = tvb ;
 }