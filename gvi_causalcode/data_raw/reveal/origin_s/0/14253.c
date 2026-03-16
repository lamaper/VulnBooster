static uint16_t * invert_lut ( uint16_t * table , int length , size_t out_length ) {
 int NumZeroes ;
 int NumPoles ;
 int i ;
 uint16_t * output = malloc ( sizeof ( uint16_t ) * out_length ) ;
 if ( ! output ) return NULL ;
 count_zeroes_and_poles ( table , length , & NumZeroes , & NumPoles ) ;
 for ( i = 0 ;
 i < out_length ;
 i ++ ) {
 double x = ( ( double ) i * 65535. ) / ( double ) ( out_length - 1 ) ;
 uint16_fract_t input = floor ( x + .5 ) ;
 output [ i ] = lut_inverse_interp16 ( input , table , length , NumZeroes , NumPoles ) ;
 }
 return output ;
 }