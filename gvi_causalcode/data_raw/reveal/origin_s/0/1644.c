static int is_compound_reference_allowed ( const VP9_COMMON * cm ) {
 int i ;
 for ( i = 1 ;
 i < REFS_PER_FRAME ;
 ++ i ) if ( cm -> ref_frame_sign_bias [ i + 1 ] != cm -> ref_frame_sign_bias [ 1 ] ) return 1 ;
 return 0 ;
 }