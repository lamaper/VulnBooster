static void U_CALLCONV uprv_writeSwapUInt32 ( uint32_t * p , uint32_t x ) {
 * p = ( uint32_t ) ( ( x << 24 ) | ( ( x << 8 ) & 0xff0000 ) | ( ( x >> 8 ) & 0xff00 ) | ( x >> 24 ) ) ;
 }