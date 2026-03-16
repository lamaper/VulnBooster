static int is_mv_diff_gt_3 ( int16_t ( * motion_val ) [ 2 ] , int step ) {
 int d ;
 d = motion_val [ 0 ] [ 0 ] - motion_val [ - step ] [ 0 ] ;
 if ( d < - 3 || d > 3 ) return 1 ;
 d = motion_val [ 0 ] [ 1 ] - motion_val [ - step ] [ 1 ] ;
 if ( d < - 3 || d > 3 ) return 1 ;
 return 0 ;
 }