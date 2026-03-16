static void vc1_loop_filter_iblk ( VC1Context * v , int pq ) {
 MpegEncContext * s = & v -> s ;
 int j ;
 if ( ! s -> first_slice_line ) {
 v -> vc1dsp . vc1_v_loop_filter16 ( s -> dest [ 0 ] , s -> linesize , pq ) ;
 if ( s -> mb_x ) v -> vc1dsp . vc1_h_loop_filter16 ( s -> dest [ 0 ] - 16 * s -> linesize , s -> linesize , pq ) ;
 v -> vc1dsp . vc1_h_loop_filter16 ( s -> dest [ 0 ] - 16 * s -> linesize + 8 , s -> linesize , pq ) ;
 for ( j = 0 ;
 j < 2 ;
 j ++ ) {
 v -> vc1dsp . vc1_v_loop_filter8 ( s -> dest [ j + 1 ] , s -> uvlinesize , pq ) ;
 if ( s -> mb_x ) v -> vc1dsp . vc1_h_loop_filter8 ( s -> dest [ j + 1 ] - 8 * s -> uvlinesize , s -> uvlinesize , pq ) ;
 }
 }
 v -> vc1dsp . vc1_v_loop_filter16 ( s -> dest [ 0 ] + 8 * s -> linesize , s -> linesize , pq ) ;
 if ( s -> mb_y == s -> end_mb_y - 1 ) {
 if ( s -> mb_x ) {
 v -> vc1dsp . vc1_h_loop_filter16 ( s -> dest [ 0 ] , s -> linesize , pq ) ;
 v -> vc1dsp . vc1_h_loop_filter8 ( s -> dest [ 1 ] , s -> uvlinesize , pq ) ;
 v -> vc1dsp . vc1_h_loop_filter8 ( s -> dest [ 2 ] , s -> uvlinesize , pq ) ;
 }
 v -> vc1dsp . vc1_h_loop_filter16 ( s -> dest [ 0 ] + 8 , s -> linesize , pq ) ;
 }
 }