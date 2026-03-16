static void * composite_memcpy ( tvbuff_t * tvb , void * _target , guint abs_offset , guint abs_length ) {
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 guint8 * target = ( guint8 * ) _target ;
 guint i , num_members ;
 tvb_comp_t * composite ;
 tvbuff_t * member_tvb = NULL ;
 guint member_offset , member_length ;
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
 return target ;
 }
 member_offset = abs_offset - composite -> start_offsets [ i ] ;
 if ( tvb_bytes_exist ( member_tvb , member_offset , abs_length ) ) {
 DISSECTOR_ASSERT ( ! tvb -> real_data ) ;
 return tvb_memcpy ( member_tvb , target , member_offset , abs_length ) ;
 }
 else {
 member_length = tvb_captured_length_remaining ( member_tvb , member_offset ) ;
 DISSECTOR_ASSERT ( member_length > 0 ) ;
 tvb_memcpy ( member_tvb , target , member_offset , member_length ) ;
 abs_offset += member_length ;
 abs_length -= member_length ;
 if ( abs_length > 0 ) {
 composite_memcpy ( tvb , target + member_length , abs_offset , abs_length ) ;
 }
 return target ;
 }
 DISSECTOR_ASSERT_NOT_REACHED ( ) ;
 }