static void make_lpc_coefs ( float * lpc , const float * refl , int order ) {
 float buf [ 100 ] ;
 float * next , * cur ;
 int m , i ;
 next = buf ;
 cur = lpc ;
 for ( m = 0 ;
 m < order ;
 m ++ ) {
 next [ m ] = refl [ m ] ;
 for ( i = 0 ;
 i < m ;
 i ++ ) next [ i ] = cur [ i ] + refl [ m ] * cur [ m - i - 1 ] ;
 FFSWAP ( float * , next , cur ) ;
 }
 if ( cur != lpc ) memcpy ( lpc , cur , sizeof ( * lpc ) * order ) ;
 }