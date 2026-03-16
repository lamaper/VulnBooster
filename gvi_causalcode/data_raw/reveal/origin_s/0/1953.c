static void copy_partitioning ( VP9_COMMON * cm , MODE_INFO * mi_8x8 , MODE_INFO * prev_mi_8x8 ) {
 const int mis = cm -> mi_stride ;
 int block_row , block_col ;
 for ( block_row = 0 ;
 block_row < 8 ;
 ++ block_row ) {
 for ( block_col = 0 ;
 block_col < 8 ;
 ++ block_col ) {
 MODE_INFO * const prev_mi = prev_mi_8x8 [ block_row * mis + block_col ] . src_mi ;
 const BLOCK_SIZE sb_type = prev_mi ? prev_mi -> mbmi . sb_type : 0 ;
 if ( prev_mi ) {
 const ptrdiff_t offset = prev_mi - cm -> prev_mi ;
 mi_8x8 [ block_row * mis + block_col ] . src_mi = cm -> mi + offset ;
 mi_8x8 [ block_row * mis + block_col ] . src_mi -> mbmi . sb_type = sb_type ;
 }
 }
 }
 }