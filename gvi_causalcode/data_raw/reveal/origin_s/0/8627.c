static void set_mode_info_seg_skip ( MACROBLOCK * x , TX_MODE tx_mode , int * rate , int64_t * dist , BLOCK_SIZE bsize ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * const mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 INTERP_FILTER filter_ref ;
 if ( xd -> up_available ) filter_ref = xd -> mi [ - xd -> mi_stride ] . src_mi -> mbmi . interp_filter ;
 else if ( xd -> left_available ) filter_ref = xd -> mi [ - 1 ] . src_mi -> mbmi . interp_filter ;
 else filter_ref = EIGHTTAP ;
 mbmi -> sb_type = bsize ;
 mbmi -> mode = ZEROMV ;
 mbmi -> tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ tx_mode ] ) ;
 mbmi -> skip = 1 ;
 mbmi -> uv_mode = DC_PRED ;
 mbmi -> ref_frame [ 0 ] = LAST_FRAME ;
 mbmi -> ref_frame [ 1 ] = NONE ;
 mbmi -> mv [ 0 ] . as_int = 0 ;
 mbmi -> interp_filter = filter_ref ;
 xd -> mi [ 0 ] . src_mi -> bmi [ 0 ] . as_mv [ 0 ] . as_int = 0 ;
 x -> skip = 1 ;
 * rate = 0 ;
 * dist = 0 ;
 }