static unsigned int block_variance ( VP9_COMP * cpi , MACROBLOCK * x , BLOCK_SIZE bs ) {
 MACROBLOCKD * xd = & x -> e_mbd ;
 unsigned int var , sse ;
 int right_overflow = ( xd -> mb_to_right_edge < 0 ) ? ( ( - xd -> mb_to_right_edge ) >> 3 ) : 0 ;
 int bottom_overflow = ( xd -> mb_to_bottom_edge < 0 ) ? ( ( - xd -> mb_to_bottom_edge ) >> 3 ) : 0 ;
 if ( right_overflow || bottom_overflow ) {
 const int bw = 8 * num_8x8_blocks_wide_lookup [ bs ] - right_overflow ;
 const int bh = 8 * num_8x8_blocks_high_lookup [ bs ] - bottom_overflow ;
 int avg ;
 variance ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , vp9_64_zeros , 0 , bw , bh , & sse , & avg ) ;
 var = sse - ( ( ( int64_t ) avg * avg ) / ( bw * bh ) ) ;
 return ( 256 * var ) / ( bw * bh ) ;
 }
 else {
 var = cpi -> fn_ptr [ bs ] . vf ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , vp9_64_zeros , 0 , & sse ) ;
 return ( 256 * var ) >> num_pels_log2_lookup [ bs ] ;
 }
 }