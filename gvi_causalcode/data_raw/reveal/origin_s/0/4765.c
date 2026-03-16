static BLOCK_SIZE get_nonrd_var_based_fixed_partition ( VP9_COMP * cpi , int mi_row , int mi_col ) {
 unsigned int var = get_sby_perpixel_diff_variance ( cpi , & cpi -> mb . plane [ 0 ] . src , mi_row , mi_col , BLOCK_64X64 ) ;
 if ( var < 4 ) return BLOCK_64X64 ;
 else if ( var < 10 ) return BLOCK_32X32 ;
 else return BLOCK_16X16 ;
 }