static void composite_free ( tvbuff_t * tvb ) {
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 tvb_comp_t * composite = & composite_tvb -> composite ;
 g_slist_free ( composite -> tvbs ) ;
 g_free ( composite -> start_offsets ) ;
 g_free ( composite -> end_offsets ) ;
 if ( tvb -> real_data ) {
 g_free ( ( gpointer ) tvb -> real_data ) ;
 }
 }