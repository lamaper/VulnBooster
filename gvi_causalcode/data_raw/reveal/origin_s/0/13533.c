static float sbr_sum_square_c ( float ( * x ) [ 2 ] , int n ) {
 float sum0 = 0.0f , sum1 = 0.0f ;
 int i ;
 for ( i = 0 ;
 i < n ;
 i += 2 ) {
 sum0 += x [ i + 0 ] [ 0 ] * x [ i + 0 ] [ 0 ] ;
 sum1 += x [ i + 0 ] [ 1 ] * x [ i + 0 ] [ 1 ] ;
 sum0 += x [ i + 1 ] [ 0 ] * x [ i + 1 ] [ 0 ] ;
 sum1 += x [ i + 1 ] [ 1 ] * x [ i + 1 ] [ 1 ] ;
 }
 return sum0 + sum1 ;
 }