static void initial_reordering_consonant_syllable ( hb_buffer_t * buffer , unsigned int start , unsigned int end ) {
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int base = end ;
 bool has_reph = false ;
 {
 unsigned int limit = start ;
 if ( start + 3 <= end && info [ start ] . myanmar_category ( ) == OT_Ra && info [ start + 1 ] . myanmar_category ( ) == OT_As && info [ start + 2 ] . myanmar_category ( ) == OT_H ) {
 limit += 3 ;
 base = start ;
 has_reph = true ;
 }
 {
 if ( ! has_reph ) base = limit ;
 for ( unsigned int i = limit ;
 i < end ;
 i ++ ) if ( is_consonant ( info [ i ] ) ) {
 base = i ;
 break ;
 }
 }
 }
 {
 unsigned int i = start ;
 for ( ;
 i < start + ( has_reph ? 3 : 0 ) ;
 i ++ ) info [ i ] . myanmar_position ( ) = POS_AFTER_MAIN ;
 for ( ;
 i < base ;
 i ++ ) info [ i ] . myanmar_position ( ) = POS_PRE_C ;
 if ( i < end ) {
 info [ i ] . myanmar_position ( ) = POS_BASE_C ;
 i ++ ;
 }
 indic_position_t pos = POS_AFTER_MAIN ;
 for ( ;
 i < end ;
 i ++ ) {
 if ( info [ i ] . myanmar_category ( ) == OT_MR ) {
 info [ i ] . myanmar_position ( ) = POS_PRE_C ;
 continue ;
 }
 if ( info [ i ] . myanmar_position ( ) < POS_BASE_C ) {
 continue ;
 }
 if ( pos == POS_AFTER_MAIN && info [ i ] . myanmar_category ( ) == OT_VBlw ) {
 pos = POS_BELOW_C ;
 info [ i ] . myanmar_position ( ) = pos ;
 continue ;
 }
 if ( pos == POS_BELOW_C && info [ i ] . myanmar_category ( ) == OT_A ) {
 info [ i ] . myanmar_position ( ) = POS_BEFORE_SUB ;
 continue ;
 }
 if ( pos == POS_BELOW_C && info [ i ] . myanmar_category ( ) == OT_VBlw ) {
 info [ i ] . myanmar_position ( ) = pos ;
 continue ;
 }
 if ( pos == POS_BELOW_C && info [ i ] . myanmar_category ( ) != OT_A ) {
 pos = POS_AFTER_SUB ;
 info [ i ] . myanmar_position ( ) = pos ;
 continue ;
 }
 info [ i ] . myanmar_position ( ) = pos ;
 }
 }
 buffer -> merge_clusters ( start , end ) ;
 hb_bubble_sort ( info + start , end - start , compare_myanmar_order ) ;
 }