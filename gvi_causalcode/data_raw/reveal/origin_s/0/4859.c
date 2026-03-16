static inline uint16_t cirrus_src16 ( CirrusVGAState * s , uint32_t srcaddr ) {
 uint16_t * src ;
 if ( s -> cirrus_srccounter ) {
 src = ( void * ) & s -> cirrus_bltbuf [ srcaddr & ( CIRRUS_BLTBUFSIZE - 1 ) & ~ 1 ] ;
 }
 else {
 src = ( void * ) & s -> vga . vram_ptr [ srcaddr & s -> cirrus_addr_mask & ~ 1 ] ;
 }
 return * src ;
 }