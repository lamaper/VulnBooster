void vp9_setup_block_planes ( MACROBLOCKD * xd , int ss_x , int ss_y ) {
 int i ;
 for ( i = 0 ;
 i < MAX_MB_PLANE ;
 i ++ ) {
 xd -> plane [ i ] . plane_type = i ? PLANE_TYPE_UV : PLANE_TYPE_Y ;
 xd -> plane [ i ] . subsampling_x = i ? ss_x : 0 ;
 xd -> plane [ i ] . subsampling_y = i ? ss_y : 0 ;
 }
 }