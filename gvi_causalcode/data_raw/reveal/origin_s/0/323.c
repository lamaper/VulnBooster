static BLOCK_SIZE get_rd_var_based_fixed_partition ( VP9_COMP * cpi , int mi_row , int mi_col ) {
 unsigned int var = get_sby_perpixel_diff_variance ( cpi , & cpi -> mb . plane [ 0 ] . src , mi_row , mi_col , BLOCK_64X64 ) ;
 if ( var < 8 ) return BLOCK_64X64 ;
 else if ( var < 128 ) return BLOCK_32X32 ;
 else if ( var < 2048 ) return BLOCK_16X16 ;
 else return BLOCK_8X8 ;
 }