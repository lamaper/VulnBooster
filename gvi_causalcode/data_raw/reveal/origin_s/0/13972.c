void compute_curve_gamma_table_type2 ( float gamma_table [ 256 ] , uint16_t * table , size_t length ) {
 unsigned int i ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 gamma_table [ i ] = lut_interp_linear ( i / 255. , table , length ) ;
 }
 }