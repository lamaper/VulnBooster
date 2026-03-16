static void initial_reordering ( const hb_ot_shape_plan_t * plan , hb_font_t * font , hb_buffer_t * buffer ) {
 update_consonant_positions ( plan , font , buffer ) ;
 insert_dotted_circles ( plan , font , buffer ) ;
 hb_glyph_info_t * info = buffer -> info ;
 unsigned int count = buffer -> len ;
 if ( unlikely ( ! count ) ) return ;
 unsigned int last = 0 ;
 unsigned int last_syllable = info [ 0 ] . syllable ( ) ;
 for ( unsigned int i = 1 ;
 i < count ;
 i ++ ) if ( last_syllable != info [ i ] . syllable ( ) ) {
 initial_reordering_syllable ( plan , font -> face , buffer , last , i ) ;
 last = i ;
 last_syllable = info [ last ] . syllable ( ) ;
 }
 initial_reordering_syllable ( plan , font -> face , buffer , last , count ) ;
 }