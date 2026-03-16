void compute_curve_gamma_table_type0 ( float gamma_table [ 256 ] ) {
 unsigned int i ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 gamma_table [ i ] = i / 255. ;
 }
 }