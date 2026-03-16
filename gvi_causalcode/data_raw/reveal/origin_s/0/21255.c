static void initial_reordering_consonant_syllable ( const hb_ot_shape_plan_t * plan , hb_face_t * face , hb_buffer_t * buffer , unsigned int start , unsigned int end ) {
 const indic_shape_plan_t * indic_plan = ( const indic_shape_plan_t * ) plan -> data ;
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int base = end ;
 bool has_reph = false ;
 {
 unsigned int limit = start ;
 if ( indic_plan -> config -> reph_pos != REPH_POS_DONT_CARE && indic_plan -> mask_array [ RPHF ] && start + 3 <= end && ( ( indic_plan -> config -> reph_mode == REPH_MODE_IMPLICIT && ! is_joiner ( info [ start + 2 ] ) ) || ( indic_plan -> config -> reph_mode == REPH_MODE_EXPLICIT && info [ start + 2 ] . indic_category ( ) == OT_ZWJ ) ) ) {
 hb_codepoint_t glyphs [ 3 ] = {
 info [ start ] . codepoint , info [ start + 1 ] . codepoint , indic_plan -> config -> reph_mode == REPH_MODE_EXPLICIT ? info [ start + 2 ] . codepoint : 0 }
 ;
 if ( indic_plan -> rphf . would_substitute ( glyphs , 2 , face ) || ( indic_plan -> config -> reph_mode == REPH_MODE_EXPLICIT && indic_plan -> rphf . would_substitute ( glyphs , 3 , face ) ) ) {
 limit += 2 ;
 while ( limit < end && is_joiner ( info [ limit ] ) ) limit ++ ;
 base = start ;
 has_reph = true ;
 }
 }
 else if ( indic_plan -> config -> reph_mode == REPH_MODE_LOG_REPHA && info [ start ] . indic_category ( ) == OT_Repha ) {
 limit += 1 ;
 while ( limit < end && is_joiner ( info [ limit ] ) ) limit ++ ;
 base = start ;
 has_reph = true ;
 }
 switch ( indic_plan -> config -> base_pos ) {
 default : assert ( false ) ;
 case BASE_POS_LAST : {
 unsigned int i = end ;
 bool seen_below = false ;
 do {
 i -- ;
 if ( is_consonant ( info [ i ] ) ) {
 if ( info [ i ] . indic_position ( ) != POS_BELOW_C && ( info [ i ] . indic_position ( ) != POS_POST_C || seen_below ) ) {
 base = i ;
 break ;
 }
 if ( info [ i ] . indic_position ( ) == POS_BELOW_C ) seen_below = true ;
 base = i ;
 }
 else {
 if ( start < i && info [ i ] . indic_category ( ) == OT_ZWJ && info [ i - 1 ] . indic_category ( ) == OT_H ) break ;
 }
 }
 while ( i > limit ) ;
 }
 break ;
 case BASE_POS_LAST_SINHALA : {
 if ( ! has_reph ) base = limit ;
 for ( unsigned int i = limit ;
 i < end ;
 i ++ ) if ( is_consonant ( info [ i ] ) ) {
 if ( limit < i && info [ i - 1 ] . indic_category ( ) == OT_ZWJ ) break ;
 else base = i ;
 }
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( is_consonant ( info [ i ] ) ) info [ i ] . indic_position ( ) = POS_BELOW_C ;
 }
 break ;
 case BASE_POS_FIRST : {
 assert ( indic_plan -> config -> reph_mode == REPH_MODE_VIS_REPHA ) ;
 assert ( ! has_reph ) ;
 base = start ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( is_consonant ( info [ i ] ) ) info [ i ] . indic_position ( ) = POS_BELOW_C ;
 }
 break ;
 }
 if ( has_reph && base == start && limit - base <= 2 ) {
 has_reph = false ;
 }
 }
 for ( unsigned int i = start ;
 i < base ;
 i ++ ) info [ i ] . indic_position ( ) = MIN ( POS_PRE_C , ( indic_position_t ) info [ i ] . indic_position ( ) ) ;
 if ( base < end ) info [ base ] . indic_position ( ) = POS_BASE_C ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( info [ i ] . indic_category ( ) == OT_M ) {
 for ( unsigned int j = i + 1 ;
 j < end ;
 j ++ ) if ( is_consonant ( info [ j ] ) ) {
 info [ j ] . indic_position ( ) = POS_FINAL_C ;
 break ;
 }
 break ;
 }
 if ( has_reph ) info [ start ] . indic_position ( ) = POS_RA_TO_BECOME_REPH ;
 if ( indic_plan -> is_old_spec ) {
 bool disallow_double_halants = buffer -> props . script != HB_SCRIPT_MALAYALAM ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( info [ i ] . indic_category ( ) == OT_H ) {
 unsigned int j ;
 for ( j = end - 1 ;
 j > i ;
 j -- ) if ( is_consonant ( info [ j ] ) || ( disallow_double_halants && info [ j ] . indic_category ( ) == OT_H ) ) break ;
 if ( info [ j ] . indic_category ( ) != OT_H && j > i ) {
 hb_glyph_info_t t = info [ i ] ;
 memmove ( & info [ i ] , & info [ i + 1 ] , ( j - i ) * sizeof ( info [ 0 ] ) ) ;
 info [ j ] = t ;
 }
 break ;
 }
 }
 {
 indic_position_t last_pos = POS_START ;
 for ( unsigned int i = start ;
 i < end ;
 i ++ ) {
 if ( ( FLAG_SAFE ( info [ i ] . indic_category ( ) ) & ( JOINER_FLAGS | FLAG ( OT_N ) | FLAG ( OT_RS ) | MEDIAL_FLAGS | HALANT_OR_COENG_FLAGS ) ) ) {
 info [ i ] . indic_position ( ) = last_pos ;
 if ( unlikely ( info [ i ] . indic_category ( ) == OT_H && info [ i ] . indic_position ( ) == POS_PRE_M ) ) {
 for ( unsigned int j = i ;
 j > start ;
 j -- ) if ( info [ j - 1 ] . indic_position ( ) != POS_PRE_M ) {
 info [ i ] . indic_position ( ) = info [ j - 1 ] . indic_position ( ) ;
 break ;
 }
 }
 }
 else if ( info [ i ] . indic_position ( ) != POS_SMVD ) {
 last_pos = ( indic_position_t ) info [ i ] . indic_position ( ) ;
 }
 }
 }
 {
 unsigned int last = base ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) if ( is_consonant ( info [ i ] ) ) {
 for ( unsigned int j = last + 1 ;
 j < i ;
 j ++ ) if ( info [ j ] . indic_position ( ) < POS_SMVD ) info [ j ] . indic_position ( ) = info [ i ] . indic_position ( ) ;
 last = i ;
 }
 else if ( info [ i ] . indic_category ( ) == OT_M ) last = i ;
 }
 {
 unsigned int syllable = info [ start ] . syllable ( ) ;
 for ( unsigned int i = start ;
 i < end ;
 i ++ ) info [ i ] . syllable ( ) = i - start ;
 hb_bubble_sort ( info + start , end - start , compare_indic_order ) ;
 base = end ;
 for ( unsigned int i = start ;
 i < end ;
 i ++ ) if ( info [ i ] . indic_position ( ) == POS_BASE_C ) {
 base = i ;
 break ;
 }
 if ( indic_plan -> is_old_spec || end - base > 127 ) buffer -> merge_clusters ( base , end ) ;
 else {
 for ( unsigned int i = base ;
 i < end ;
 i ++ ) if ( info [ i ] . syllable ( ) != 255 ) {
 unsigned int max = i ;
 unsigned int j = start + info [ i ] . syllable ( ) ;
 while ( j != i ) {
 max = MAX ( max , j ) ;
 unsigned int next = start + info [ j ] . syllable ( ) ;
 info [ j ] . syllable ( ) = 255 ;
 j = next ;
 }
 if ( i != max ) buffer -> merge_clusters ( i , max + 1 ) ;
 }
 }
 for ( unsigned int i = start ;
 i < end ;
 i ++ ) info [ i ] . syllable ( ) = syllable ;
 }
 {
 hb_mask_t mask ;
 for ( unsigned int i = start ;
 i < end && info [ i ] . indic_position ( ) == POS_RA_TO_BECOME_REPH ;
 i ++ ) info [ i ] . mask |= indic_plan -> mask_array [ RPHF ] ;
 mask = indic_plan -> mask_array [ HALF ] ;
 if ( ! indic_plan -> is_old_spec && indic_plan -> config -> blwf_mode == BLWF_MODE_PRE_AND_POST ) mask |= indic_plan -> mask_array [ BLWF ] ;
 for ( unsigned int i = start ;
 i < base ;
 i ++ ) info [ i ] . mask |= mask ;
 mask = 0 ;
 if ( base < end ) info [ base ] . mask |= mask ;
 mask = indic_plan -> mask_array [ BLWF ] | indic_plan -> mask_array [ ABVF ] | indic_plan -> mask_array [ PSTF ] ;
 for ( unsigned int i = base + 1 ;
 i < end ;
 i ++ ) info [ i ] . mask |= mask ;
 }
 if ( indic_plan -> is_old_spec && buffer -> props . script == HB_SCRIPT_DEVANAGARI ) {
 for ( unsigned int i = start ;
 i + 1 < base ;
 i ++ ) if ( info [ i ] . indic_category ( ) == OT_Ra && info [ i + 1 ] . indic_category ( ) == OT_H && ( i + 2 == base || info [ i + 2 ] . indic_category ( ) != OT_ZWJ ) ) {
 info [ i ] . mask |= indic_plan -> mask_array [ BLWF ] ;
 info [ i + 1 ] . mask |= indic_plan -> mask_array [ BLWF ] ;
 }
 }
 unsigned int pref_len = indic_plan -> config -> pref_len ;
 if ( indic_plan -> mask_array [ PREF ] && base + pref_len < end ) {
 assert ( 1 <= pref_len && pref_len <= 2 ) ;
 for ( unsigned int i = base + 1 ;
 i + pref_len - 1 < end ;
 i ++ ) {
 hb_codepoint_t glyphs [ 2 ] ;
 for ( unsigned int j = 0 ;
 j < pref_len ;
 j ++ ) glyphs [ j ] = info [ i + j ] . codepoint ;
 if ( indic_plan -> pref . would_substitute ( glyphs , pref_len , face ) ) {
 for ( unsigned int j = 0 ;
 j < pref_len ;
 j ++ ) info [ i ++ ] . mask |= indic_plan -> mask_array [ PREF ] ;
 if ( indic_plan -> mask_array [ CFAR ] ) for ( ;
 i < end ;
 i ++ ) info [ i ] . mask |= indic_plan -> mask_array [ CFAR ] ;
 break ;
 }
 }
 }
 for ( unsigned int i = start + 1 ;
 i < end ;
 i ++ ) if ( is_joiner ( info [ i ] ) ) {
 bool non_joiner = info [ i ] . indic_category ( ) == OT_ZWNJ ;
 unsigned int j = i ;
 do {
 j -- ;
 if ( non_joiner ) info [ j ] . mask &= ~ indic_plan -> mask_array [ HALF ] ;
 }
 while ( j > start && ! is_consonant ( info [ j ] ) ) ;
 }
 }