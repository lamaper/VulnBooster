static void nuke_joiners ( const hb_ot_shape_plan_t * plan HB_UNUSED , hb_font_t * font HB_UNUSED , hb_buffer_t * buffer ) {
 unsigned int count = buffer -> len ;
 hb_glyph_info_t * info = buffer -> info ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) if ( _hb_glyph_info_is_zwj ( & info [ i ] ) ) _hb_glyph_info_flip_joiners ( & info [ i ] ) ;
 }