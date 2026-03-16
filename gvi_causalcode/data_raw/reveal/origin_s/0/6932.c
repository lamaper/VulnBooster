static int rollstack ( struct psstack * stack , int sp ) {
 int n , j , i ;
 struct psstack * temp ;
 if ( sp > 1 ) {
 n = stack [ sp - 2 ] . u . val ;
 j = stack [ sp - 1 ] . u . val ;
 sp -= 2 ;
 if ( sp >= n && n > 0 ) {
 j %= n ;
 if ( j < 0 ) j += n ;
 temp = malloc ( n * sizeof ( struct psstack ) ) ;
 for ( i = 0 ;
 i < n ;
 ++ i ) temp [ i ] = stack [ sp - n + i ] ;
 for ( i = 0 ;
 i < n ;
 ++ i ) stack [ sp - n + ( i + j ) % n ] = temp [ i ] ;
 free ( temp ) ;
 }
 }
 return ( sp ) ;
 }