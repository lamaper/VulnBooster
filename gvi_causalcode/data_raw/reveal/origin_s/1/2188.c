static void final_reordering ( const hb_ot_shape_plan_t * plan , hb_font_t * font HB_UNUSED , hb_buffer_t * buffer ) {
 unsigned int count = buffer -> len ;
 if ( unlikely ( ! count ) ) return ;
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int last = 0 ;
 unsigned int last_syllable = info [ 0 ] . syllable ( ) ;
 for ( unsigned int i = 1 ;
 i < count ;
 i ++ ) if ( last_syllable != info [ i ] . syllable ( ) ) {
 final_reordering_syllable ( plan , buffer , last , i ) ;
 last = i ;
 last_syllable = info [ last ] . syllable ( ) ;
 }
 final_reordering_syllable ( plan , buffer , last , count ) ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , indic_category ) ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , indic_position ) ;
 }