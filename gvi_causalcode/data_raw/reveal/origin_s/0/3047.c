static inline uint8_t vga_read_byte ( VGACommonState * vga , uint32_t addr ) {
 return vga -> vram_ptr [ addr & vga -> vbe_size_mask ] ;
 }