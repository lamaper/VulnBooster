static inline uint8_t cirrus_src ( CirrusVGAState * s , uint32_t srcaddr ) {
 if ( s -> cirrus_srccounter ) {
 return s -> cirrus_bltbuf [ srcaddr & ( CIRRUS_BLTBUFSIZE - 1 ) ] ;
 }
 else {
 return s -> vga . vram_ptr [ srcaddr & s -> cirrus_addr_mask ] ;
 }
 }