BN_ULONG bn_add_words ( BN_ULONG * r , const BN_ULONG * a , const BN_ULONG * b , int n ) {
 BN_ULONG c , l , t ;
 assert ( n >= 0 ) ;
 if ( n <= 0 ) return ( ( BN_ULONG ) 0 ) ;
 c = 0 ;

 t = a [ 0 ] ;
 t = ( t + c ) & BN_MASK2 ;
 c = ( t < c ) ;
 l = ( t + b [ 0 ] ) & BN_MASK2 ;
 c += ( l < t ) ;
 r [ 0 ] = l ;
 t = a [ 1 ] ;
 t = ( t + c ) & BN_MASK2 ;
 c = ( t < c ) ;
 l = ( t + b [ 1 ] ) & BN_MASK2 ;
 c += ( l < t ) ;
 r [ 1 ] = l ;
 t = a [ 2 ] ;
 t = ( t + c ) & BN_MASK2 ;
 c = ( t < c ) ;
 l = ( t + b [ 2 ] ) & BN_MASK2 ;
 c += ( l < t ) ;
 r [ 2 ] = l ;
 t = a [ 3 ] ;
 t = ( t + c ) & BN_MASK2 ;
 c = ( t < c ) ;
 l = ( t + b [ 3 ] ) & BN_MASK2 ;
 c += ( l < t ) ;
 r [ 3 ] = l ;
 a += 4 ;
 b += 4 ;
 r += 4 ;
 n -= 4 ;
 }

 t = a [ 0 ] ;
 t = ( t + c ) & BN_MASK2 ;
 c = ( t < c ) ;
 l = ( t + b [ 0 ] ) & BN_MASK2 ;
 c += ( l < t ) ;
 r [ 0 ] = l ;
 a ++ ;
 b ++ ;
 r ++ ;
 n -- ;
 }
 return ( ( BN_ULONG ) c ) ;
 }