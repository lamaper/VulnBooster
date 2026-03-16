static inline uint32_t vga_read_dword_le ( VGACommonState * vga , uint32_t addr ) {
 uint32_t offset = addr & vga -> vbe_size_mask & ~ 3 ;
 uint32_t * ptr = ( uint32_t * ) ( vga -> vram_ptr + offset ) ;
 return ldl_le_p ( ptr ) ;
 }