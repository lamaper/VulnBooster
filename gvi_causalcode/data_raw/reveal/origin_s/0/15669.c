static uint16_t * build_pow_table ( float gamma , int length ) {
 int i ;
 uint16_t * output = malloc ( sizeof ( uint16_t ) * length ) ;
 if ( ! output ) return NULL ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 uint16_fract_t result ;
 double x = ( ( double ) i ) / ( double ) ( length - 1 ) ;
 x = pow ( x , gamma ) ;
 result = floor ( x * 65535. + .5 ) ;
 output [ i ] = result ;
 }
 return output ;
 }