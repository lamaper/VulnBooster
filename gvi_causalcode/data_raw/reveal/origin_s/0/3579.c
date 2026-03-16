static int set_vt_partitioning ( VP9_COMP * cpi , void * data , BLOCK_SIZE bsize , int mi_row , int mi_col ) {
 VP9_COMMON * const cm = & cpi -> common ;
 variance_node vt ;
 const int block_width = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int block_height = num_8x8_blocks_high_lookup [ bsize ] ;
 const int64_t threshold_multiplier = 25 ;
 int64_t threshold = threshold_multiplier * cpi -> common . base_qindex ;
 assert ( block_height == block_width ) ;
 tree_to_node ( data , bsize , & vt ) ;
 if ( mi_col + block_width / 2 < cm -> mi_cols && mi_row + block_height / 2 < cm -> mi_rows && vt . part_variances -> none . variance < threshold ) {
 set_block_size ( cpi , mi_row , mi_col , bsize ) ;
 return 1 ;
 }
 if ( mi_row + block_height / 2 < cm -> mi_rows && vt . part_variances -> vert [ 0 ] . variance < threshold && vt . part_variances -> vert [ 1 ] . variance < threshold ) {
 BLOCK_SIZE subsize = get_subsize ( bsize , PARTITION_VERT ) ;
 set_block_size ( cpi , mi_row , mi_col , subsize ) ;
 set_block_size ( cpi , mi_row , mi_col + block_width / 2 , subsize ) ;
 return 1 ;
 }
 if ( mi_col + block_width / 2 < cm -> mi_cols && vt . part_variances -> horz [ 0 ] . variance < threshold && vt . part_variances -> horz [ 1 ] . variance < threshold ) {
 BLOCK_SIZE subsize = get_subsize ( bsize , PARTITION_HORZ ) ;
 set_block_size ( cpi , mi_row , mi_col , subsize ) ;
 set_block_size ( cpi , mi_row + block_height / 2 , mi_col , subsize ) ;
 return 1 ;
 }
 return 0 ;
 }