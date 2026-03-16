static inline void NVRAM_set_byte ( m48t59_t * nvram , uint32_t addr , uint8_t value ) {
 m48t59_set_addr ( nvram , addr ) ;
 m48t59_write ( nvram , value ) ;
 }