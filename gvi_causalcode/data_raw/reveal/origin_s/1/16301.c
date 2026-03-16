static void read_intra_frame_mode_info ( VP9_COMMON * const cm , MACROBLOCKD * const xd , int mi_row , int mi_col , vp9_reader * r ) {
 MODE_INFO * const mi = xd -> mi [ 0 ] ;
 MB_MODE_INFO * const mbmi = & mi -> mbmi ;
 const MODE_INFO * above_mi = xd -> mi [ - cm -> mi_stride ] ;
 const MODE_INFO * left_mi = xd -> left_available ? xd -> mi [ - 1 ] : NULL ;
 const BLOCK_SIZE bsize = mbmi -> sb_type ;
 int i ;
 mbmi -> segment_id = read_intra_segment_id ( cm , xd , mi_row , mi_col , r ) ;
 mbmi -> skip = read_skip ( cm , xd , mbmi -> segment_id , r ) ;
 mbmi -> tx_size = read_tx_size ( cm , xd , cm -> tx_mode , bsize , 1 , r ) ;
 mbmi -> ref_frame [ 0 ] = INTRA_FRAME ;
 mbmi -> ref_frame [ 1 ] = NONE ;
 switch ( bsize ) {
 case BLOCK_4X4 : for ( i = 0 ;
 i < 4 ;
 ++ i ) mi -> bmi [ i ] . as_mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , i ) ) ;
 mbmi -> mode = mi -> bmi [ 3 ] . as_mode ;
 break ;
 case BLOCK_4X8 : mi -> bmi [ 0 ] . as_mode = mi -> bmi [ 2 ] . as_mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , 0 ) ) ;
 mi -> bmi [ 1 ] . as_mode = mi -> bmi [ 3 ] . as_mode = mbmi -> mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , 1 ) ) ;
 break ;
 case BLOCK_8X4 : mi -> bmi [ 0 ] . as_mode = mi -> bmi [ 1 ] . as_mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , 0 ) ) ;
 mi -> bmi [ 2 ] . as_mode = mi -> bmi [ 3 ] . as_mode = mbmi -> mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , 2 ) ) ;
 break ;
 default : mbmi -> mode = read_intra_mode ( r , get_y_mode_probs ( mi , above_mi , left_mi , 0 ) ) ;
 }
 mbmi -> uv_mode = read_intra_mode ( r , vp9_kf_uv_mode_prob [ mbmi -> mode ] ) ;
 }