static void final_reordering ( const hb_ot_shape_plan_t * plan , hb_font_t * font HB_UNUSED , hb_buffer_t * buffer ) {
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int count = buffer -> len ;
 for ( unsigned int i = 0 ;
 i < count ;
 i ++ ) info [ i ] . syllable ( ) = 0 ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , myanmar_category ) ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , myanmar_position ) ;
 }