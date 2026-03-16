static int output_to_inttgt ( int output ) {
 int i ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( inttgt_output ) ;
 i ++ ) {
 if ( inttgt_output [ i ] [ 1 ] == output ) {
 return inttgt_output [ i ] [ 0 ] ;
 }
 }
 abort ( ) ;
 }