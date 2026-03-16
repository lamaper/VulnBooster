static void build_inter_predictors_for_planes ( MACROBLOCKD * xd , BLOCK_SIZE bsize , int mi_row , int mi_col , int plane_from , int plane_to ) {
 int plane ;
 const int mi_x = mi_col * MI_SIZE ;
 const int mi_y = mi_row * MI_SIZE ;
 for ( plane = plane_from ;
 plane <= plane_to ;
 ++ plane ) {
 const BLOCK_SIZE plane_bsize = get_plane_block_size ( bsize , & xd -> plane [ plane ] ) ;
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ plane_bsize ] ;
 const int bw = 4 * num_4x4_w ;
 const int bh = 4 * num_4x4_h ;
 if ( xd -> mi [ 0 ] . src_mi -> mbmi . sb_type < BLOCK_8X8 ) {
 int i = 0 , x , y ;
 assert ( bsize == BLOCK_8X8 ) ;
 for ( y = 0 ;
 y < num_4x4_h ;
 ++ y ) for ( x = 0 ;
 x < num_4x4_w ;
 ++ x ) build_inter_predictors ( xd , plane , i ++ , bw , bh , * x , 4 * y , 4 , 4 , mi_x , mi_y ) ;
 }
 else {
 build_inter_predictors ( xd , plane , 0 , bw , bh , 0 , 0 , bw , bh , mi_x , mi_y ) ;
 }
 }
 }