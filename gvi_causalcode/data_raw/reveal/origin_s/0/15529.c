static inline uint32_t cirrus_src32 ( CirrusVGAState * s , uint32_t srcaddr ) {
 uint32_t * src ;
 if ( s -> cirrus_srccounter ) {
 src = ( void * ) & s -> cirrus_bltbuf [ srcaddr & ( CIRRUS_BLTBUFSIZE - 1 ) & ~ 3 ] ;
 }
 else {
 src = ( void * ) & s -> vga . vram_ptr [ srcaddr & s -> cirrus_addr_mask & ~ 3 ] ;
 }
 return * src ;
 }