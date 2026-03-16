void MatInverse ( real into [ 6 ] , real orig [ 6 ] ) {
 real det = orig [ 0 ] * orig [ 3 ] - orig [ 1 ] * orig [ 2 ] ;
 if ( det == 0 ) {
 LogError ( _ ( "Attempt to invert a singular matrix\n" ) ) ;
 memset ( into , 0 , sizeof ( * into ) ) ;
 }
 else {
 into [ 0 ] = orig [ 3 ] / det ;
 into [ 1 ] = - orig [ 1 ] / det ;
 into [ 2 ] = - orig [ 2 ] / det ;
 into [ 3 ] = orig [ 0 ] / det ;
 into [ 4 ] = - orig [ 4 ] * into [ 0 ] - orig [ 5 ] * into [ 2 ] ;
 into [ 5 ] = - orig [ 4 ] * into [ 1 ] - orig [ 5 ] * into [ 3 ] ;
 }
 }