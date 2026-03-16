static void rd_encode_breakout_test ( VP9_COMP * cpi , MACROBLOCK * x , BLOCK_SIZE bsize , int * rate2 , int64_t * distortion , int64_t * distortion_uv , int * disable_skip ) {
 VP9_COMMON * cm = & cpi -> common ;
 MACROBLOCKD * xd = & x -> e_mbd ;
 const BLOCK_SIZE y_size = get_plane_block_size ( bsize , & xd -> plane [ 0 ] ) ;
 const BLOCK_SIZE uv_size = get_plane_block_size ( bsize , & xd -> plane [ 1 ] ) ;
 unsigned int var , sse ;
 unsigned int thresh_ac ;
 unsigned int thresh_dc ;
 var = cpi -> fn_ptr [ y_size ] . vf ( x -> plane [ 0 ] . src . buf , x -> plane [ 0 ] . src . stride , xd -> plane [ 0 ] . dst . buf , xd -> plane [ 0 ] . dst . stride , & sse ) ;
 if ( x -> encode_breakout > 0 ) {
 const unsigned int max_thresh = ( cpi -> allow_encode_breakout == ENCODE_BREAKOUT_LIMITED ) ? 128 : 36000 ;
 const unsigned int min_thresh = MIN ( ( ( unsigned int ) x -> encode_breakout << 4 ) , max_thresh ) ;
 thresh_ac = ( xd -> plane [ 0 ] . dequant [ 1 ] * xd -> plane [ 0 ] . dequant [ 1 ] ) / 9 ;
 thresh_ac = clamp ( thresh_ac , min_thresh , max_thresh ) ;
 thresh_ac >>= 8 - ( b_width_log2 ( bsize ) + b_height_log2 ( bsize ) ) ;
 thresh_dc = ( xd -> plane [ 0 ] . dequant [ 0 ] * xd -> plane [ 0 ] . dequant [ 0 ] >> 6 ) ;
 }
 else {
 thresh_ac = 0 ;
 thresh_dc = 0 ;
 }
 if ( sse < thresh_ac || sse == 0 ) {
 if ( ( sse - var ) < thresh_dc || sse == var ) {
 unsigned int sse_u , sse_v ;
 unsigned int var_u , var_v ;
 var_u = cpi -> fn_ptr [ uv_size ] . vf ( x -> plane [ 1 ] . src . buf , x -> plane [ 1 ] . src . stride , xd -> plane [ 1 ] . dst . buf , xd -> plane [ 1 ] . dst . stride , & sse_u ) ;
 if ( ( sse_u * 4 < thresh_ac || sse_u == 0 ) && ( sse_u - var_u < thresh_dc || sse_u == var_u ) ) {
 var_v = cpi -> fn_ptr [ uv_size ] . vf ( x -> plane [ 2 ] . src . buf , x -> plane [ 2 ] . src . stride , xd -> plane [ 2 ] . dst . buf , xd -> plane [ 2 ] . dst . stride , & sse_v ) ;
 if ( ( sse_v * 4 < thresh_ac || sse_v == 0 ) && ( sse_v - var_v < thresh_dc || sse_v == var_v ) ) {
 x -> skip = 1 ;
 * rate2 += vp9_cost_bit ( vp9_get_skip_prob ( cm , xd ) , 1 ) ;
 * distortion_uv = ( sse_u + sse_v ) << 4 ;
 * distortion = ( sse << 4 ) + * distortion_uv ;
 * disable_skip = 1 ;
 }
 }
 }
 }
 }