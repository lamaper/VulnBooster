static void final_reordering ( const hb_ot_shape_plan_t * plan , hb_font_t * font HB_UNUSED , hb_buffer_t * buffer ) {
 unsigned int count = buffer -> len ;
 if ( unlikely ( ! count ) ) return ;
 foreach_syllable ( buffer , start , end ) final_reordering_syllable ( plan , buffer , start , end ) ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , indic_category ) ;
 HB_BUFFER_DEALLOCATE_VAR ( buffer , indic_position ) ;
 }