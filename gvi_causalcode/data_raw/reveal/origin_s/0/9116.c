void validate_gamma_table ( float gamma_table [ 256 ] ) {
 int i ;
 for ( i = 0 ;
 i < 256 ;
 i ++ ) {
 if ( ! ( gamma_table [ i ] >= 0.f && gamma_table [ i ] <= 1.f ) ) {
 gamma_table [ i ] = 0.f ;
 }
 }
 }