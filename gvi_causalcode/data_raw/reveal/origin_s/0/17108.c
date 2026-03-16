static void initial_reordering ( const hb_ot_shape_plan_t * plan , hb_font_t * font , hb_buffer_t * buffer ) {
 insert_dotted_circles ( plan , font , buffer ) ;
 foreach_syllable ( buffer , start , end ) initial_reordering_syllable ( plan , font -> face , buffer , start , end ) ;
 }