static int check_best_zero_mv ( const VP9_COMP * cpi , const uint8_t mode_context [ MAX_REF_FRAMES ] , int_mv frame_mv [ MB_MODE_COUNT ] [ MAX_REF_FRAMES ] , int inter_mode_mask , int this_mode , const MV_REFERENCE_FRAME ref_frames [ 2 ] ) {
 if ( ( inter_mode_mask & ( 1 << ZEROMV ) ) && ( this_mode == NEARMV || this_mode == NEARESTMV || this_mode == ZEROMV ) && frame_mv [ this_mode ] [ ref_frames [ 0 ] ] . as_int == 0 && ( ref_frames [ 1 ] == NONE || frame_mv [ this_mode ] [ ref_frames [ 1 ] ] . as_int == 0 ) ) {
 int rfc = mode_context [ ref_frames [ 0 ] ] ;
 int c1 = cost_mv_ref ( cpi , NEARMV , rfc ) ;
 int c2 = cost_mv_ref ( cpi , NEARESTMV , rfc ) ;
 int c3 = cost_mv_ref ( cpi , ZEROMV , rfc ) ;
 if ( this_mode == NEARMV ) {
 if ( c1 > c3 ) return 0 ;
 }
 else if ( this_mode == NEARESTMV ) {
 if ( c2 > c3 ) return 0 ;
 }
 else {
 assert ( this_mode == ZEROMV ) ;
 if ( ref_frames [ 1 ] == NONE ) {
 if ( ( c3 >= c2 && frame_mv [ NEARESTMV ] [ ref_frames [ 0 ] ] . as_int == 0 ) || ( c3 >= c1 && frame_mv [ NEARMV ] [ ref_frames [ 0 ] ] . as_int == 0 ) ) return 0 ;
 }
 else {
 if ( ( c3 >= c2 && frame_mv [ NEARESTMV ] [ ref_frames [ 0 ] ] . as_int == 0 && frame_mv [ NEARESTMV ] [ ref_frames [ 1 ] ] . as_int == 0 ) || ( c3 >= c1 && frame_mv [ NEARMV ] [ ref_frames [ 0 ] ] . as_int == 0 && frame_mv [ NEARMV ] [ ref_frames [ 1 ] ] . as_int == 0 ) ) return 0 ;
 }
 }
 }
 return 1 ;
 }