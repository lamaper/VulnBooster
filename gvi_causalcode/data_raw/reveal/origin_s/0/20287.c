static uint32_t U_CALLCONV uprv_readSwapUInt32 ( uint32_t x ) {
 return ( uint32_t ) ( ( x << 24 ) | ( ( x << 8 ) & 0xff0000 ) | ( ( x >> 8 ) & 0xff00 ) | ( x >> 24 ) ) ;
 }