void bn_sqr_words ( BN_ULONG * r , const BN_ULONG * a , int n ) {
 assert ( n >= 0 ) ;
 if ( n <= 0 ) return ;

 sqr64 ( r [ 0 ] , r [ 1 ] , a [ 0 ] ) ;
 sqr64 ( r [ 2 ] , r [ 3 ] , a [ 1 ] ) ;
 sqr64 ( r [ 4 ] , r [ 5 ] , a [ 2 ] ) ;
 sqr64 ( r [ 6 ] , r [ 7 ] , a [ 3 ] ) ;
 a += 4 ;
 r += 8 ;
 n -= 4 ;
 }

 sqr64 ( r [ 0 ] , r [ 1 ] , a [ 0 ] ) ;
 a ++ ;
 r += 2 ;
 n -- ;
 }
 }