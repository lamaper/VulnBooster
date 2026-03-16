static void setup_plane_dequants ( VP9_COMMON * cm , MACROBLOCKD * xd , int q_index ) {
 int i ;
 xd -> plane [ 0 ] . dequant = cm -> y_dequant [ q_index ] ;
 for ( i = 1 ;
 i < MAX_MB_PLANE ;
 i ++ ) xd -> plane [ i ] . dequant = cm -> uv_dequant [ q_index ] ;
 }