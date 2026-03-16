void _hb_ot_shape_normalize ( const hb_ot_shape_plan_t * plan , hb_buffer_t * buffer , hb_font_t * font ) {
 _hb_buffer_assert_unicode_vars ( buffer ) ;
 hb_ot_shape_normalization_mode_t mode = plan -> shaper -> normalization_preference ;
 const hb_ot_shape_normalize_context_t c = {
 plan , buffer , font , buffer -> unicode , plan -> shaper -> decompose ? plan -> shaper -> decompose : decompose_unicode , plan -> shaper -> compose ? plan -> shaper -> compose : compose_unicode }
 ;
 bool always_short_circuit = mode == HB_OT_SHAPE_NORMALIZATION_MODE_NONE ;
 bool might_short_circuit = always_short_circuit || ( mode != HB_OT_SHAPE_NORMALIZATION_MODE_DECOMPOSED && mode != HB_OT_SHAPE_NORMALIZATION_MODE_COMPOSED_DIACRITICS_NO_SHORT_CIRCUIT ) ;
 unsigned int count ;
 buffer -> clear_output ( ) ;
 count = buffer -> len ;
 for ( buffer -> idx = 0 ;
 buffer -> idx < count ;
 ) {
 unsigned int end ;
 for ( end = buffer -> idx + 1 ;
 end < count ;
 end ++ ) if ( buffer -> cur ( ) . cluster != buffer -> info [ end ] . cluster ) break ;
 decompose_cluster ( & c , end , might_short_circuit , always_short_circuit ) ;
 }
 buffer -> swap_buffers ( ) ;
 count = buffer -> len ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) {
 if ( _hb_glyph_info_get_modified_combining_class ( & buffer -> info [ i ] ) == 0 ) continue ;
 unsigned int end ;
 for ( end = i + 1 ;
 end < count ;
 end ++ ) if ( _hb_glyph_info_get_modified_combining_class ( & buffer -> info [ end ] ) == 0 ) break ;
 if ( end - i > 10 ) {
 i = end ;
 continue ;
 }
 hb_bubble_sort ( buffer -> info + i , end - i , compare_combining_class ) ;
 i = end ;
 }
 if ( mode == HB_OT_SHAPE_NORMALIZATION_MODE_NONE || mode == HB_OT_SHAPE_NORMALIZATION_MODE_DECOMPOSED ) return ;
 buffer -> clear_output ( ) ;
 count = buffer -> len ;
 unsigned int starter = 0 ;
 buffer -> next_glyph ( ) ;
 while ( buffer -> idx < count ) {
 hb_codepoint_t composed , glyph ;
 if ( HB_UNICODE_GENERAL_CATEGORY_IS_MARK ( _hb_glyph_info_get_general_category ( & buffer -> cur ( ) ) ) && ( starter == buffer -> out_len - 1 || _hb_glyph_info_get_modified_combining_class ( & buffer -> prev ( ) ) < _hb_glyph_info_get_modified_combining_class ( & buffer -> cur ( ) ) ) && c . compose ( & c , buffer -> out_info [ starter ] . codepoint , buffer -> cur ( ) . codepoint , & composed ) && font -> get_glyph ( composed , 0 , & glyph ) ) {
 buffer -> next_glyph ( ) ;
 if ( unlikely ( buffer -> in_error ) ) return ;
 buffer -> merge_out_clusters ( starter , buffer -> out_len ) ;
 buffer -> out_len -- ;
 buffer -> out_info [ starter ] . codepoint = composed ;
 buffer -> out_info [ starter ] . glyph_index ( ) = glyph ;
 _hb_glyph_info_set_unicode_props ( & buffer -> out_info [ starter ] , buffer -> unicode ) ;
 continue ;
 }
 buffer -> next_glyph ( ) ;
 if ( _hb_glyph_info_get_modified_combining_class ( & buffer -> prev ( ) ) == 0 ) starter = buffer -> out_len - 1 ;
 }
 buffer -> swap_buffers ( ) ;
 }