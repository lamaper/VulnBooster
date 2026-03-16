static void read_frame_reference_mode_probs ( VP9_COMMON * cm , vp9_reader * r ) {
 FRAME_CONTEXT * const fc = & cm -> fc ;
 int i ;
 if ( cm -> reference_mode == REFERENCE_MODE_SELECT ) for ( i = 0 ;
 i < COMP_INTER_CONTEXTS ;
 ++ i ) vp9_diff_update_prob ( r , & fc -> comp_inter_prob [ i ] ) ;
 if ( cm -> reference_mode != COMPOUND_REFERENCE ) for ( i = 0 ;
 i < REF_CONTEXTS ;
 ++ i ) {
 vp9_diff_update_prob ( r , & fc -> single_ref_prob [ i ] [ 0 ] ) ;
 vp9_diff_update_prob ( r , & fc -> single_ref_prob [ i ] [ 1 ] ) ;
 }
 if ( cm -> reference_mode != SINGLE_REFERENCE ) for ( i = 0 ;
 i < REF_CONTEXTS ;
 ++ i ) vp9_diff_update_prob ( r , & fc -> comp_ref_prob [ i ] ) ;
 }