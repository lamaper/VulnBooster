static void preprocess_text_hangul ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , hb_font_t * font ) {
 HB_BUFFER_ALLOCATE_VAR ( buffer , hangul_shaping_feature ) ;
 buffer -> clear_output ( ) ;
 unsigned int start = 0 , end = 0 ;
 unsigned int count = buffer -> len ;
 for ( buffer -> idx = 0 ;
 buffer -> idx < count ;
 ) {
 hb_codepoint_t u = buffer -> cur ( ) . codepoint ;
 if ( isHangulTone ( u ) ) {
 if ( start < end && end == buffer -> out_len ) {
 buffer -> next_glyph ( ) ;
 if ( ! is_zero_width_char ( font , u ) ) {
 hb_glyph_info_t * info = buffer -> out_info ;
 hb_glyph_info_t tone = info [ end ] ;
 memmove ( & info [ start + 1 ] , & info [ start ] , ( end - start ) * sizeof ( hb_glyph_info_t ) ) ;
 info [ start ] = tone ;
 buffer -> merge_out_clusters ( start , end + 1 ) ;
 }
 }
 else {
 if ( font -> has_glyph ( 0x25CCu ) ) {
 hb_codepoint_t chars [ 2 ] ;
 if ( ! is_zero_width_char ( font , u ) ) {
 chars [ 0 ] = u ;
 chars [ 1 ] = 0x25CCu ;
 }
 else {
 chars [ 0 ] = 0x25CCu ;
 chars [ 1 ] = u ;
 }
 buffer -> replace_glyphs ( 1 , 2 , chars ) ;
 }
 else {
 buffer -> next_glyph ( ) ;
 }
 }
 start = end = buffer -> out_len ;
 continue ;
 }
 start = buffer -> out_len ;
 if ( isL ( u ) && buffer -> idx + 1 < count ) {
 hb_codepoint_t l = u ;
 hb_codepoint_t v = buffer -> cur ( + 1 ) . codepoint ;
 if ( isV ( v ) ) {
 hb_codepoint_t t = 0 ;
 unsigned int tindex = 0 ;
 if ( buffer -> idx + 2 < count ) {
 t = buffer -> cur ( + 2 ) . codepoint ;
 if ( isT ( t ) ) tindex = t - TBase ;
 else t = 0 ;
 }
 if ( isCombiningL ( l ) && isCombiningV ( v ) && ( t == 0 || isCombiningT ( t ) ) ) {
 hb_codepoint_t s = SBase + ( l - LBase ) * NCount + ( v - VBase ) * TCount + tindex ;
 if ( font -> has_glyph ( s ) ) {
 buffer -> replace_glyphs ( t ? 3 : 2 , 1 , & s ) ;
 if ( unlikely ( buffer -> in_error ) ) return ;
 end = start + 1 ;
 continue ;
 }
 }
 buffer -> cur ( ) . hangul_shaping_feature ( ) = LJMO ;
 buffer -> next_glyph ( ) ;
 buffer -> cur ( ) . hangul_shaping_feature ( ) = VJMO ;
 buffer -> next_glyph ( ) ;
 if ( t ) {
 buffer -> cur ( ) . hangul_shaping_feature ( ) = TJMO ;
 buffer -> next_glyph ( ) ;
 end = start + 3 ;
 }
 else end = start + 2 ;
 if ( buffer -> cluster_level == HB_BUFFER_CLUSTER_LEVEL_MONOTONE_GRAPHEMES ) buffer -> merge_out_clusters ( start , end ) ;
 continue ;
 }
 }
 else if ( isCombinedS ( u ) ) {
 hb_codepoint_t s = u ;
 bool has_glyph = font -> has_glyph ( s ) ;
 unsigned int lindex = ( s - SBase ) / NCount ;
 unsigned int nindex = ( s - SBase ) % NCount ;
 unsigned int vindex = nindex / TCount ;
 unsigned int tindex = nindex % TCount ;
 if ( ! tindex && buffer -> idx + 1 < count && isCombiningT ( buffer -> cur ( + 1 ) . codepoint ) ) {
 unsigned int new_tindex = buffer -> cur ( + 1 ) . codepoint - TBase ;
 hb_codepoint_t new_s = s + new_tindex ;
 if ( font -> has_glyph ( new_s ) ) {
 buffer -> replace_glyphs ( 2 , 1 , & new_s ) ;
 if ( unlikely ( buffer -> in_error ) ) return ;
 end = start + 1 ;
 continue ;
 }
 }
 if ( ! has_glyph || ( ! tindex && buffer -> idx + 1 < count && isT ( buffer -> cur ( + 1 ) . codepoint ) ) ) {
 hb_codepoint_t decomposed [ 3 ] = {
 LBase + lindex , VBase + vindex , TBase + tindex }
 ;
 if ( font -> has_glyph ( decomposed [ 0 ] ) && font -> has_glyph ( decomposed [ 1 ] ) && ( ! tindex || font -> has_glyph ( decomposed [ 2 ] ) ) ) {
 unsigned int s_len = tindex ? 3 : 2 ;
 buffer -> replace_glyphs ( 1 , s_len , decomposed ) ;
 if ( unlikely ( buffer -> in_error ) ) return ;
 hb_glyph_info_t * info = buffer -> out_info ;
 if ( has_glyph && ! tindex ) {
 buffer -> next_glyph ( ) ;
 s_len ++ ;
 }
 end = start + s_len ;
 unsigned int i = start ;
 info [ i ++ ] . hangul_shaping_feature ( ) = LJMO ;
 info [ i ++ ] . hangul_shaping_feature ( ) = VJMO ;
 if ( i < end ) info [ i ++ ] . hangul_shaping_feature ( ) = TJMO ;
 if ( buffer -> cluster_level == HB_BUFFER_CLUSTER_LEVEL_MONOTONE_GRAPHEMES ) buffer -> merge_out_clusters ( start , end ) ;
 continue ;
 }
 }
 if ( has_glyph ) {
 end = start + 1 ;
 buffer -> next_glyph ( ) ;
 continue ;
 }
 }
 buffer -> next_glyph ( ) ;
 }
 buffer -> swap_buffers ( ) ;
 }