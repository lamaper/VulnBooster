int MatIsIdentity ( real transform [ 6 ] ) {
 return ( transform [ 0 ] == 1 && transform [ 3 ] == 1 && transform [ 1 ] == 0 && transform [ 2 ] == 0 && transform [ 4 ] == 0 && transform [ 5 ] == 0 ) ;
 }