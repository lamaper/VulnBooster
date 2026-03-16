static BLOCK_SIZE get_bsize ( const VP9_COMMON * cm , int mb_row , int mb_col ) {
 if ( 2 * mb_col + 1 < cm -> mi_cols ) {
 return 2 * mb_row + 1 < cm -> mi_rows ? BLOCK_16X16 : BLOCK_16X8 ;
 }
 else {
 return 2 * mb_row + 1 < cm -> mi_rows ? BLOCK_8X16 : BLOCK_8X8 ;
 }
 }