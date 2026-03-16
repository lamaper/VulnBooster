int32_t itostr ( char * buffer , int32_t i , uint32_t radix , int32_t pad ) {
 const char digits [ 16 ] = {
 '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , 'a' , 'b' , 'c' , 'd' , 'e' , 'f' }
 ;
 int32_t length = 0 ;
 int32_t num = 0 ;
 int32_t save = i ;
 int digit ;
 int32_t j ;
 char temp ;
 if ( i < 0 ) {
 i = - i ;
 }
 do {
 digit = ( int ) ( i % radix ) ;
 buffer [ length ++ ] = digits [ digit ] ;
 i = i / radix ;
 }
 while ( i ) ;
 while ( length < pad ) {
 buffer [ length ++ ] = '0' ;
 }
 if ( save < 0 ) {
 buffer [ length ++ ] = '-' ;
 }
 if ( length < MAX_DIGITS ) {
 buffer [ length ] = 0x0000 ;
 }
 num = ( pad >= length ) ? pad : length ;
 for ( j = 0 ;
 j < ( num / 2 ) ;
 j ++ ) {
 temp = buffer [ ( length - 1 ) - j ] ;
 buffer [ ( length - 1 ) - j ] = buffer [ j ] ;
 buffer [ j ] = temp ;
 }
 return length ;
 }