static int getDynamicOffset ( uint32_t c , uint32_t * pOffset ) {
 int i ;
 for ( i = 0 ;
 i < 7 ;
 ++ i ) {
 if ( ( uint32_t ) ( c - fixedOffsets [ i ] ) <= 0x7f ) {
 * pOffset = fixedOffsets [ i ] ;
 return 0xf9 + i ;
 }
 }
 if ( c < 0x80 ) {
 return - 1 ;
 }
 else if ( c < 0x3400 || ( uint32_t ) ( c - 0x10000 ) < ( 0x14000 - 0x10000 ) || ( uint32_t ) ( c - 0x1d000 ) <= ( 0x1ffff - 0x1d000 ) ) {
 * pOffset = c & 0x7fffff80 ;
 return ( int ) ( c >> 7 ) ;
 }
 else if ( 0xe000 <= c && c != 0xfeff && c < 0xfff0 ) {
 * pOffset = c & 0x7fffff80 ;
 return ( int ) ( ( c - gapOffset ) >> 7 ) ;
 }
 else {
 return - 1 ;
 }
 }