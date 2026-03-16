static void get_sb_partition_size_range ( MACROBLOCKD * xd , MODE_INFO * mi_8x8 , BLOCK_SIZE * min_block_size , BLOCK_SIZE * max_block_size , int bs_hist [ BLOCK_SIZES ] ) {
 int sb_width_in_blocks = MI_BLOCK_SIZE ;
 int sb_height_in_blocks = MI_BLOCK_SIZE ;
 int i , j ;
 int index = 0 ;
 for ( i = 0 ;
 i < sb_height_in_blocks ;
 ++ i ) {
 for ( j = 0 ;
 j < sb_width_in_blocks ;
 ++ j ) {
 MODE_INFO * mi = mi_8x8 [ index + j ] . src_mi ;
 BLOCK_SIZE sb_type = mi ? mi -> mbmi . sb_type : 0 ;
 bs_hist [ sb_type ] ++ ;
 * min_block_size = MIN ( * min_block_size , sb_type ) ;
 * max_block_size = MAX ( * max_block_size , sb_type ) ;
 }
 index += xd -> mi_stride ;
 }
 }