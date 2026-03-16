static inline uint16_t vga_read_word_le ( VGACommonState * vga , uint32_t addr ) {
 uint32_t offset = addr & vga -> vbe_size_mask & ~ 1 ;
 uint16_t * ptr = ( uint16_t * ) ( vga -> vram_ptr + offset ) ;
 return lduw_le_p ( ptr ) ;
 }