static uint16_t U_CALLCONV uprv_readSwapUInt16 ( uint16_t x ) {
 return ( uint16_t ) ( ( x << 8 ) | ( x >> 8 ) ) ;
 }