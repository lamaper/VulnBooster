static inline void NVRAM_set_word ( m48t59_t * nvram , uint32_t addr , uint16_t value ) {
 m48t59_set_addr ( nvram , addr ) ;
 m48t59_write ( nvram , value >> 8 ) ;
 m48t59_set_addr ( nvram , addr + 1 ) ;
 m48t59_write ( nvram , value & 0xFF ) ;
 }