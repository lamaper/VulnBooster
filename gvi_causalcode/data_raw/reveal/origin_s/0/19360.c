void build_output_lut ( struct curveType * trc , uint16_t * * output_gamma_lut , size_t * output_gamma_lut_length ) {
 if ( trc -> type == PARAMETRIC_CURVE_TYPE ) {
 float gamma_table [ 256 ] ;
 uint16_t gamma_table_uint [ 256 ] ;
 uint16_t i ;
 uint16_t * inverted ;
 int inverted_size = 4096 ;
 compute_curve_gamma_table_type_parametric ( gamma_table , trc -> parameter , trc -> count ) ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 gamma_table_uint [ i ] = ( uint16_t ) ( gamma_table [ i ] * 65535 ) ;
 }
 inverted = invert_lut ( gamma_table_uint , 256 , inverted_size ) ;
 if ( ! inverted ) return ;
 * output_gamma_lut = inverted ;
 * output_gamma_lut_length = inverted_size ;
 }
 else {
 if ( trc -> count == 0 ) {
 * output_gamma_lut = build_linear_table ( 4096 ) ;
 * output_gamma_lut_length = 4096 ;
 }
 else if ( trc -> count == 1 ) {
 float gamma = 1. / u8Fixed8Number_to_float ( trc -> data [ 0 ] ) ;
 * output_gamma_lut = build_pow_table ( gamma , 4096 ) ;
 * output_gamma_lut_length = 4096 ;
 }
 else {
 * output_gamma_lut_length = trc -> count ;
 if ( * output_gamma_lut_length < 256 ) * output_gamma_lut_length = 256 ;
 * output_gamma_lut = invert_lut ( trc -> data , trc -> count , * output_gamma_lut_length ) ;
 }
 }
 }