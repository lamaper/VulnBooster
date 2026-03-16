void MatMultiply ( real m1 [ 6 ] , real m2 [ 6 ] , real to [ 6 ] ) {
 real trans [ 6 ] ;
 trans [ 0 ] = m1 [ 0 ] * m2 [ 0 ] + m1 [ 1 ] * m2 [ 2 ] ;
 trans [ 1 ] = m1 [ 0 ] * m2 [ 1 ] + m1 [ 1 ] * m2 [ 3 ] ;
 trans [ 2 ] = m1 [ 2 ] * m2 [ 0 ] + m1 [ 3 ] * m2 [ 2 ] ;
 trans [ 3 ] = m1 [ 2 ] * m2 [ 1 ] + m1 [ 3 ] * m2 [ 3 ] ;
 trans [ 4 ] = m1 [ 4 ] * m2 [ 0 ] + m1 [ 5 ] * m2 [ 2 ] + m2 [ 4 ] ;
 trans [ 5 ] = m1 [ 4 ] * m2 [ 1 ] + m1 [ 5 ] * m2 [ 3 ] + m2 [ 5 ] ;
 memcpy ( to , trans , sizeof ( trans ) ) ;
 }