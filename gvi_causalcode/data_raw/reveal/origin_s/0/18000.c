static float * calc_distr ( const float * p , int n , int m , float rest ) {
 float * row , * prev_row , * tmp ;
 int i , j ;
 row = ( float * ) palloc ( ( m + 1 ) * sizeof ( float ) ) ;
 prev_row = ( float * ) palloc ( ( m + 1 ) * sizeof ( float ) ) ;
 row [ 0 ] = 1.0f ;
 for ( i = 1 ;
 i <= n ;
 i ++ ) {
 float t = p [ i - 1 ] ;
 tmp = row ;
 row = prev_row ;
 prev_row = tmp ;
 for ( j = 0 ;
 j <= i && j <= m ;
 j ++ ) {
 float val = 0.0f ;
 if ( j < i ) val += prev_row [ j ] * ( 1.0f - t ) ;
 if ( j > 0 ) val += prev_row [ j - 1 ] * t ;
 row [ j ] = val ;
 }
 }
 if ( rest > DEFAULT_CONTAIN_SEL ) {
 float t ;
 tmp = row ;
 row = prev_row ;
 prev_row = tmp ;
 for ( i = 0 ;
 i <= m ;
 i ++ ) row [ i ] = 0.0f ;
 t = exp ( - rest ) ;
 for ( i = 0 ;
 i <= m ;
 i ++ ) {
 for ( j = 0 ;
 j <= m - i ;
 j ++ ) row [ j + i ] += prev_row [ j ] * t ;
 t *= rest / ( float ) ( i + 1 ) ;
 }
 }
 pfree ( prev_row ) ;
 return row ;
 }