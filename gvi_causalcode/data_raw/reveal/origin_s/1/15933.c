static void choose_partitioning ( VP9_COMP * cpi , const TileInfo * const tile , int mi_row , int mi_col ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * x = & cpi -> mb ;
 MACROBLOCKD * xd = & cpi -> mb . e_mbd ;
 int i , j , k ;
 v64x64 vt ;
 uint8_t * s ;
 const uint8_t * d ;
 int sp ;
 int dp ;
 int pixels_wide = 64 , pixels_high = 64 ;
 int_mv nearest_mv , near_mv ;
 const YV12_BUFFER_CONFIG * yv12 = get_ref_frame_buffer ( cpi , LAST_FRAME ) ;
 const struct scale_factors * const sf = & cm -> frame_refs [ LAST_FRAME - 1 ] . sf ;
 vp9_zero ( vt ) ;
 set_offsets ( cpi , tile , mi_row , mi_col , BLOCK_64X64 ) ;
 if ( xd -> mb_to_right_edge < 0 ) pixels_wide += ( xd -> mb_to_right_edge >> 3 ) ;
 if ( xd -> mb_to_bottom_edge < 0 ) pixels_high += ( xd -> mb_to_bottom_edge >> 3 ) ;
 s = x -> plane [ 0 ] . src . buf ;
 sp = x -> plane [ 0 ] . src . stride ;
 if ( cm -> frame_type != KEY_FRAME ) {
 vp9_setup_pre_planes ( xd , 0 , yv12 , mi_row , mi_col , sf ) ;
 xd -> mi [ 0 ] -> mbmi . ref_frame [ 0 ] = LAST_FRAME ;
 xd -> mi [ 0 ] -> mbmi . sb_type = BLOCK_64X64 ;
 vp9_find_best_ref_mvs ( xd , cm -> allow_high_precision_mv , xd -> mi [ 0 ] -> mbmi . ref_mvs [ LAST_FRAME ] , & nearest_mv , & near_mv ) ;
 xd -> mi [ 0 ] -> mbmi . mv [ 0 ] = nearest_mv ;
 vp9_build_inter_predictors_sby ( xd , mi_row , mi_col , BLOCK_64X64 ) ;
 d = xd -> plane [ 0 ] . dst . buf ;
 dp = xd -> plane [ 0 ] . dst . stride ;
 }
 else {
 d = VP9_VAR_OFFS ;
 dp = 0 ;
 }
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 const int x32_idx = ( ( i & 1 ) << 5 ) ;
 const int y32_idx = ( ( i >> 1 ) << 5 ) ;
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 const int x16_idx = x32_idx + ( ( j & 1 ) << 4 ) ;
 const int y16_idx = y32_idx + ( ( j >> 1 ) << 4 ) ;
 v16x16 * vst = & vt . split [ i ] . split [ j ] ;
 for ( k = 0 ;
 k < 4 ;
 k ++ ) {
 int x_idx = x16_idx + ( ( k & 1 ) << 3 ) ;
 int y_idx = y16_idx + ( ( k >> 1 ) << 3 ) ;
 unsigned int sse = 0 ;
 int sum = 0 ;
 if ( x_idx < pixels_wide && y_idx < pixels_high ) vp9_get8x8var ( s + y_idx * sp + x_idx , sp , d + y_idx * dp + x_idx , dp , & sse , & sum ) ;
 fill_variance ( sse , sum , 64 , & vst -> split [ k ] . part_variances . none ) ;
 }
 }
 }
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 for ( j = 0 ;
 j < 4 ;
 j ++ ) {
 fill_variance_tree ( & vt . split [ i ] . split [ j ] , BLOCK_16X16 ) ;
 }
 fill_variance_tree ( & vt . split [ i ] , BLOCK_32X32 ) ;
 }
 fill_variance_tree ( & vt , BLOCK_64X64 ) ;
 if ( ! set_vt_partitioning ( cpi , & vt , BLOCK_64X64 , mi_row , mi_col ) ) {
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 const int x32_idx = ( ( i & 1 ) << 2 ) ;
 const int y32_idx = ( ( i >> 1 ) << 2 ) ;
 if ( ! set_vt_partitioning ( cpi , & vt . split [ i ] , BLOCK_32X32 , ( mi_row + y32_idx ) , ( mi_col + x32_idx ) ) ) {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) {
 const int x16_idx = ( ( j & 1 ) << 1 ) ;
 const int y16_idx = ( ( j >> 1 ) << 1 ) ;

 set_block_size ( cpi , ( mi_row + y32_idx + y16_idx ) , ( mi_col + x32_idx + x16_idx ) , BLOCK_16X16 ) ;
 }
 else {
 for ( k = 0 ;
 k < 4 ;
 ++ k ) {
 const int x8_idx = ( k & 1 ) ;
 const int y8_idx = ( k >> 1 ) ;
 set_block_size ( cpi , ( mi_row + y32_idx + y16_idx + y8_idx ) , ( mi_col + x32_idx + x16_idx + x8_idx ) , BLOCK_8X8 ) ;
 }
 }

 for ( k = 0 ;
 k < 4 ;
 ++ k ) {
 const int x8_idx = ( k & 1 ) ;
 const int y8_idx = ( k >> 1 ) ;
 set_block_size ( cpi , ( mi_row + y32_idx + y16_idx + y8_idx ) , ( mi_col + x32_idx + x16_idx + x8_idx ) , BLOCK_8X8 ) ;
 }
 }

 }
 }
 }
 }