static int sb_has_motion ( const VP9_COMMON * cm , MODE_INFO * * prev_mi_8x8 , const int motion_thresh ) {
 const int mis = cm -> mi_stride ;
 int block_row , block_col ;
 if ( cm -> prev_mi ) {
 for ( block_row = 0 ;
 block_row < 8 ;
 ++ block_row ) {
 for ( block_col = 0 ;
 block_col < 8 ;
 ++ block_col ) {
 const MODE_INFO * prev_mi = prev_mi_8x8 [ block_row * mis + block_col ] ;
 if ( prev_mi ) {
 if ( abs ( prev_mi -> mbmi . mv [ 0 ] . as_mv . row ) > motion_thresh || abs ( prev_mi -> mbmi . mv [ 0 ] . as_mv . col ) > motion_thresh ) return 1 ;
 }
 }
 }
 }
 return 0 ;
 }