static void U_CALLCONV uprv_writeSwapUInt16 ( uint16_t * p , uint16_t x ) {
 * p = ( uint16_t ) ( ( x << 8 ) | ( x >> 8 ) ) ;
 }