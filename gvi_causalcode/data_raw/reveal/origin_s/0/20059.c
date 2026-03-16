static void initial_reordering_standalone_cluster ( const hb_ot_shape_plan_t * plan , hb_face_t * face , hb_buffer_t * buffer , unsigned int start , unsigned int end ) {
 if ( hb_options ( ) . uniscribe_bug_compatible ) {
 if ( buffer -> info [ end - 1 ] . indic_category ( ) == OT_DOTTEDCIRCLE ) return ;
 }
 initial_reordering_consonant_syllable ( plan , face , buffer , start , end ) ;
 }