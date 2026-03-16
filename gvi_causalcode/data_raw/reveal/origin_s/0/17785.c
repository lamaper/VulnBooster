static inline uint16_t NVRAM_get_word ( m48t59_t * nvram , uint32_t addr ) {
 uint16_t tmp ;
 m48t59_set_addr ( nvram , addr ) ;
 tmp = m48t59_read ( nvram ) << 8 ;
 m48t59_set_addr ( nvram , addr + 1 ) ;
 tmp |= m48t59_read ( nvram ) ;
 return tmp ;
 }