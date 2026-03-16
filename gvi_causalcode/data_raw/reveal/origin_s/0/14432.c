static void final_reordering_syllable ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , unsigned int start , unsigned int end ) {
 const indic_shape_plan_t * indic_plan = ( const indic_shape_plan_t * ) plan -> data ;
 hb_glyph_info_t * info = buffer -> info ;
 if ( indic_plan -> virama_glyph ) {
 unsigned int virama_glyph = indic_plan -> virama_glyph ;
 for ( unsigned int i = start ;
 i < end ;
 i ++ ) if ( info [ i ] . codepoint == virama_glyph && _hb_glyph_info_ligated ( & info [ i ] ) && _hb_glyph_info_multiplied ( & info [ i ] ) ) {
 info [ i ] . indic_category ( ) = OT_H ;
 _hb_glyph_info_clear_ligated_and_multiplied ( & info [ i ] ) ;
 }
 }
 bool try_pref = ! ! indic_plan -> mask_array [ PREF ] ;
 unsigned int base ;
 for ( base = start ;
 base < end ;
 base ++ ) if ( info [ base ] . indic_position ( ) >= POS_BASE_C ) {
 if ( try_pref && base + 1 < end && indic_plan -> config -> pref_len == 2 ) {
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( ( info [ i ] . mask & indic_plan -> mask_array [ PREF ] ) != 0 ) {
 if ( ! ( _hb_glyph_info_substituted ( & info [ i ] ) && _hb_glyph_info_ligated_and_didnt_multiply ( & info [ i ] ) ) ) {
 base = i ;
 while ( base < end && is_halant_or_coeng ( info [ base ] ) ) base ++ ;
 info [ base ] . indic_position ( ) = POS_BASE_C ;
 try_pref = false ;
 }
 break ;
 }
 }
 if ( start < base && info [ base ] . indic_position ( ) > POS_BASE_C ) base -- ;
 break ;
 }
 if ( base == end && start < base && is_one_of ( info [ base - 1 ] , FLAG ( OT_ZWJ ) ) ) base -- ;
 if ( base < end ) while ( start < base && is_one_of ( info [ base ] , ( FLAG ( OT_N ) | HALANT_OR_COENG_FLAGS ) ) ) base -- ;
 if ( start + 1 < end && start < base ) {
 unsigned int new_pos = base == end ? base - 2 : base - 1 ;
 if ( buffer -> props . script != HB_SCRIPT_MALAYALAM && buffer -> props . script != HB_SCRIPT_TAMIL ) {
 while ( new_pos > start && ! ( is_one_of ( info [ new_pos ] , ( FLAG ( OT_M ) | HALANT_OR_COENG_FLAGS ) ) ) ) new_pos -- ;
 if ( is_halant_or_coeng ( info [ new_pos ] ) && info [ new_pos ] . indic_position ( ) != POS_PRE_M ) {
 if ( new_pos + 1 < end && is_joiner ( info [ new_pos + 1 ] ) ) new_pos ++ ;
 }
 else new_pos = start ;
 }
 if ( start < new_pos && info [ new_pos ] . indic_position ( ) != POS_PRE_M ) {
 for ( unsigned int i = new_pos ;
 i > start ;
 i -- ) if ( info [ i - 1 ] . indic_position ( ) == POS_PRE_M ) {
 unsigned int old_pos = i - 1 ;
 hb_glyph_info_t tmp = info [ old_pos ] ;
 memmove ( & info [ old_pos ] , & info [ old_pos + 1 ] , ( new_pos - old_pos ) * sizeof ( info [ 0 ] ) ) ;
 info [ new_pos ] = tmp ;
 if ( old_pos < base && base <= new_pos ) base -- ;
 buffer -> merge_clusters ( new_pos , MIN ( end , base + 1 ) ) ;
 new_pos -- ;
 }
 }
 else {
 for ( unsigned int i = start ;
 i < base ;
 i ++ ) if ( info [ i ] . indic_position ( ) == POS_PRE_M ) {
 buffer -> merge_clusters ( i , MIN ( end , base + 1 ) ) ;
 break ;
 }
 }
 }
 if ( start + 1 < end && info [ start ] . indic_position ( ) == POS_RA_TO_BECOME_REPH && ( ( info [ start ] . indic_category ( ) == OT_Repha ) ^ _hb_glyph_info_ligated_and_didnt_multiply ( & info [ start ] ) ) ) {
 unsigned int new_reph_pos ;
 reph_position_t reph_pos = indic_plan -> config -> reph_pos ;
 assert ( reph_pos != REPH_POS_DONT_CARE ) ;
 if ( reph_pos == REPH_POS_AFTER_POST ) {
 goto reph_step_5 ;
 }
 {
 new_reph_pos = start + 1 ;
 while ( new_reph_pos < base && ! is_halant_or_coeng ( info [ new_reph_pos ] ) ) new_reph_pos ++ ;
 if ( new_reph_pos < base && is_halant_or_coeng ( info [ new_reph_pos ] ) ) {
 if ( new_reph_pos + 1 < base && is_joiner ( info [ new_reph_pos + 1 ] ) ) new_reph_pos ++ ;
 goto reph_move ;
 }
 }
 if ( reph_pos == REPH_POS_AFTER_MAIN ) {
 new_reph_pos = base ;
 while ( new_reph_pos + 1 < end && info [ new_reph_pos + 1 ] . indic_position ( ) <= POS_AFTER_MAIN ) new_reph_pos ++ ;
 if ( new_reph_pos < end ) goto reph_move ;
 }
 if ( reph_pos == REPH_POS_AFTER_SUB ) {
 new_reph_pos = base ;
 while ( new_reph_pos < end && ! ( FLAG_SAFE ( info [ new_reph_pos + 1 ] . indic_position ( ) ) & ( FLAG ( POS_POST_C ) | FLAG ( POS_AFTER_POST ) | FLAG ( POS_SMVD ) ) ) ) new_reph_pos ++ ;
 if ( new_reph_pos < end ) goto reph_move ;
 }
 reph_step_5 : {
 new_reph_pos = start + 1 ;
 while ( new_reph_pos < base && ! is_halant_or_coeng ( info [ new_reph_pos ] ) ) new_reph_pos ++ ;
 if ( new_reph_pos < base && is_halant_or_coeng ( info [ new_reph_pos ] ) ) {
 if ( new_reph_pos + 1 < base && is_joiner ( info [ new_reph_pos + 1 ] ) ) new_reph_pos ++ ;
 goto reph_move ;
 }
 }
 {
 new_reph_pos = end - 1 ;
 while ( new_reph_pos > start && info [ new_reph_pos ] . indic_position ( ) == POS_SMVD ) new_reph_pos -- ;
 if ( ! hb_options ( ) . uniscribe_bug_compatible && unlikely ( is_halant_or_coeng ( info [ new_reph_pos ] ) ) ) {
 for ( unsigned int i = base + 1 ;
 i < new_reph_pos ;
 i ++ ) if ( info [ i ] . indic_category ( ) == OT_M ) {
 new_reph_pos -- ;
 }
 }
 goto reph_move ;
 }
 reph_move : {
 buffer -> merge_clusters ( start , new_reph_pos + 1 ) ;
 hb_glyph_info_t reph = info [ start ] ;
 memmove ( & info [ start ] , & info [ start + 1 ] , ( new_reph_pos - start ) * sizeof ( info [ 0 ] ) ) ;
 info [ new_reph_pos ] = reph ;
 if ( start < base && base <= new_reph_pos ) base -- ;
 }
 }
 if ( try_pref && base + 1 < end ) {
 unsigned int pref_len = indic_plan -> config -> pref_len ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( ( info [ i ] . mask & indic_plan -> mask_array [ PREF ] ) != 0 ) {
 if ( _hb_glyph_info_substituted ( & info [ i ] ) && ( ( pref_len == 1 ) ^ _hb_glyph_info_ligated_and_didnt_multiply ( & info [ i ] ) ) ) {
 unsigned int new_pos = base ;
 if ( buffer -> props . script != HB_SCRIPT_MALAYALAM && buffer -> props . script != HB_SCRIPT_TAMIL ) {
 while ( new_pos > start && ! ( is_one_of ( info [ new_pos - 1 ] , FLAG ( OT_M ) | HALANT_OR_COENG_FLAGS ) ) ) new_pos -- ;
 if ( new_pos > start && info [ new_pos - 1 ] . indic_category ( ) == OT_M ) {
 unsigned int old_pos = i ;
 for ( unsigned int i = base + 1 ;
 i < old_pos ;
 i ++ ) if ( info [ i ] . indic_category ( ) == OT_M ) {
 new_pos -- ;
 break ;
 }
 }
 }
 if ( new_pos > start && is_halant_or_coeng ( info [ new_pos - 1 ] ) ) {
 if ( new_pos < end && is_joiner ( info [ new_pos ] ) ) new_pos ++ ;
 }
 {
 unsigned int old_pos = i ;
 buffer -> merge_clusters ( new_pos , old_pos + 1 ) ;
 hb_glyph_info_t tmp = info [ old_pos ] ;
 memmove ( & info [ new_pos + 1 ] , & info [ new_pos ] , ( old_pos - new_pos ) * sizeof ( info [ 0 ] ) ) ;
 info [ new_pos ] = tmp ;
 if ( new_pos <= base && base < old_pos ) base ++ ;
 }
 }
 break ;
 }
 }
 if ( info [ start ] . indic_position ( ) == POS_PRE_M && ( ! start || ! ( FLAG_SAFE ( _hb_glyph_info_get_general_category ( & info [ start - 1 ] ) ) & FLAG_RANGE ( HB_UNICODE_GENERAL_CATEGORY_FORMAT , HB_UNICODE_GENERAL_CATEGORY_NON_SPACING_MARK ) ) ) ) info [ start ] . mask |= indic_plan -> mask_array [ INIT ] ;
 if ( hb_options ( ) . uniscribe_bug_compatible ) {
 switch ( ( hb_tag_t ) plan -> props . script ) {
 case HB_SCRIPT_TAMIL : case HB_SCRIPT_SINHALA : break ;
 default : buffer -> merge_clusters ( start , end ) ;
 break ;
 }
 }
 }