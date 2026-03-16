void vp9_set_mv_search_range ( MACROBLOCK * x , const MV * mv ) {
 int col_min = ( mv -> col >> 3 ) - MAX_FULL_PEL_VAL + ( mv -> col & 7 ? 1 : 0 ) ;
 int row_min = ( mv -> row >> 3 ) - MAX_FULL_PEL_VAL + ( mv -> row & 7 ? 1 : 0 ) ;
 int col_max = ( mv -> col >> 3 ) + MAX_FULL_PEL_VAL ;
 int row_max = ( mv -> row >> 3 ) + MAX_FULL_PEL_VAL ;
 col_min = MAX ( col_min , ( MV_LOW >> 3 ) + 1 ) ;
 row_min = MAX ( row_min , ( MV_LOW >> 3 ) + 1 ) ;
 col_max = MIN ( col_max , ( MV_UPP >> 3 ) - 1 ) ;
 row_max = MIN ( row_max , ( MV_UPP >> 3 ) - 1 ) ;
 if ( x -> mv_col_min < col_min ) x -> mv_col_min = col_min ;
 if ( x -> mv_col_max > col_max ) x -> mv_col_max = col_max ;
 if ( x -> mv_row_min < row_min ) x -> mv_row_min = row_min ;
 if ( x -> mv_row_max > row_max ) x -> mv_row_max = row_max ;
 }