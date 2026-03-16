static void initial_reordering_syllable ( const hb_ot_shape_plan_t * plan , hb_face_t * face , hb_buffer_t * buffer , unsigned int start , unsigned int end ) {
 syllable_type_t syllable_type = ( syllable_type_t ) ( buffer -> info [ start ] . syllable ( ) & 0x0F ) ;
 switch ( syllable_type ) {
 case vowel_syllable : case consonant_syllable : initial_reordering_consonant_syllable ( plan , face , buffer , start , end ) ;
 break ;
 case broken_cluster : case standalone_cluster : initial_reordering_standalone_cluster ( plan , face , buffer , start , end ) ;
 break ;
 case symbol_cluster : case non_indic_cluster : break ;
 }
 }