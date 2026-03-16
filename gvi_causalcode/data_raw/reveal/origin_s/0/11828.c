static void sum_intra_stats ( FRAME_COUNTS * counts , const MODE_INFO * mi ) {
 const PREDICTION_MODE y_mode = mi -> mbmi . mode ;
 const PREDICTION_MODE uv_mode = mi -> mbmi . uv_mode ;
 const BLOCK_SIZE bsize = mi -> mbmi . sb_type ;
 if ( bsize < BLOCK_8X8 ) {
 int idx , idy ;
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ bsize ] ;
 for ( idy = 0 ;
 idy < 2 ;
 idy += num_4x4_h ) for ( idx = 0 ;
 idx < 2 ;
 idx += num_4x4_w ) ++ counts -> y_mode [ 0 ] [ mi -> bmi [ idy * 2 + idx ] . as_mode ] ;
 }
 else {
 ++ counts -> y_mode [ size_group_lookup [ bsize ] ] [ y_mode ] ;
 }
 ++ counts -> uv_mode [ y_mode ] [ uv_mode ] ;
 }