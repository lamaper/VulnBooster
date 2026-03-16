static inline uint8_t NVRAM_get_byte ( m48t59_t * nvram , uint32_t addr ) {
 m48t59_set_addr ( nvram , addr ) ;
 return m48t59_read ( nvram ) ;
 }