static int8_t getWindow ( const uint32_t offsets [ 8 ] , uint32_t c ) {
 int i ;
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 if ( ( uint32_t ) ( c - offsets [ i ] ) <= 0x7f ) {
 return ( int8_t ) ( i ) ;
 }
 }
 return - 1 ;
 }