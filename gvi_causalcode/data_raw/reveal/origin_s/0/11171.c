static void Transform ( BasePoint * to , DBasePoint * from , real trans [ 6 ] ) {
 to -> x = trans [ 0 ] * from -> x + trans [ 2 ] * from -> y + trans [ 4 ] ;
 to -> y = trans [ 1 ] * from -> x + trans [ 3 ] * from -> y + trans [ 5 ] ;
 }