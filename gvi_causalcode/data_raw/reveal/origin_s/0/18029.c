static uint16_t * build_linear_table ( int length ) {
 int i ;
 uint16_t * output = malloc ( sizeof ( uint16_t ) * length ) ;
 if ( ! output ) return NULL ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 double x = ( ( double ) i * 65535. ) / ( double ) ( length - 1 ) ;
 uint16_fract_t input = floor ( x + .5 ) ;
 output [ i ] = input ;
 }
 return output ;
 }