static inline uint32_t NVRAM_get_lword ( m48t59_t * nvram , uint32_t addr ) {
 uint32_t tmp ;
 m48t59_set_addr ( nvram , addr ) ;
 tmp = m48t59_read ( nvram ) << 24 ;
 m48t59_set_addr ( nvram , addr + 1 ) ;
 tmp |= m48t59_read ( nvram ) << 16 ;
 m48t59_set_addr ( nvram , addr + 2 ) ;
 tmp |= m48t59_read ( nvram ) << 8 ;
 m48t59_set_addr ( nvram , addr + 3 ) ;
 tmp |= m48t59_read ( nvram ) ;
 return tmp ;
 }