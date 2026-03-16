static void vc1_apply_p_loop_filter ( VC1Context * v ) {
 MpegEncContext * s = & v -> s ;
 int i ;
 for ( i = 0 ;
 i < 6 ;
 i ++ ) {
 vc1_apply_p_v_loop_filter ( v , i ) ;
 }
 if ( s -> mb_x ) {
 for ( i = 0 ;
 i < 6 ;
 i ++ ) {
 vc1_apply_p_h_loop_filter ( v , i ) ;
 }
 if ( s -> mb_x == s -> mb_width - 1 ) {
 s -> mb_x ++ ;
 ff_update_block_index ( s ) ;
 for ( i = 0 ;
 i < 6 ;
 i ++ ) {
 vc1_apply_p_h_loop_filter ( v , i ) ;
 }
 }
 }
 }