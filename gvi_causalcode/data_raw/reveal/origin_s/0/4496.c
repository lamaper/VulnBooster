static const guint8 * composite_get_ptr ( tvbuff_t * tvb , guint abs_offset , guint abs_length ) {
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 guint i , num_members ;
 tvb_comp_t * composite ;
 tvbuff_t * member_tvb = NULL ;
 guint member_offset ;
 GSList * slist ;
 composite = & composite_tvb -> composite ;
 num_members = g_slist_length ( composite -> tvbs ) ;
 for ( i = 0 ;
 i < num_members ;
 i ++ ) {
 if ( abs_offset <= composite -> end_offsets [ i ] ) {
 slist = g_slist_nth ( composite -> tvbs , i ) ;
 member_tvb = ( tvbuff_t * ) slist -> data ;
 break ;
 }
 }
 if ( ! member_tvb ) {
 DISSECTOR_ASSERT ( abs_offset == tvb -> length && abs_length == 0 ) ;
 return "" ;
 }
 member_offset = abs_offset - composite -> start_offsets [ i ] ;
 if ( tvb_bytes_exist ( member_tvb , member_offset , abs_length ) ) {
 DISSECTOR_ASSERT ( ! tvb -> real_data ) ;
 return tvb_get_ptr ( member_tvb , member_offset , abs_length ) ;
 }
 else {
 void * real_data = g_malloc ( tvb -> length ) ;
 tvb_memcpy ( tvb , real_data , 0 , tvb -> length ) ;
 tvb -> real_data = ( const guint8 * ) real_data ;
 return tvb -> real_data + abs_offset ;
 }
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }