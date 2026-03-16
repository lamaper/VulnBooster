static void prep_NVRAM_init ( void ) {
 m48t59_t * nvram ;
 nvram = m48t59_init ( 8 , 0x0074 , NVRAM_SIZE ) ;
 NVRAM_set_word ( nvram , 0x00 , NVRAM_SIZE >> 10 ) ;
 NVRAM_set_byte ( nvram , 0x02 , 0x01 ) ;
 NVRAM_set_byte ( nvram , 0x03 , 0x01 ) ;
 NVRAM_set_byte ( nvram , 0x08 , 0x00 ) ;
 NVRAM_set_byte ( nvram , 0x09 , 'B' ) ;
 NVRAM_set_byte ( nvram , 0x0A , 0x00 ) ;
 NVRAM_set_byte ( nvram , 0x0B , 0x00 ) ;
 NVRAM_set_word ( nvram , 0x0C , 0x01 ) ;
 NVRAM_set_word ( nvram , 0x0E , 0x01 ) ;
 NVRAM_set_lword ( nvram , 0x20 , 0x00 ) ;
 NVRAM_set_lword ( nvram , 0x24 , 0x00 ) ;
 NVRAM_set_lword ( nvram , 0x28 , 0x00 ) ;
 NVRAM_set_crc ( nvram , 0x1C , 0x0C , 32 ) ;
 NVRAM_set_lword ( nvram , 0xC4 , 0x0100 ) ;
 NVRAM_set_lword ( nvram , 0xC8 , NVRAM_END - NVRAM_OSAREA_SIZE - NVRAM_CONFSIZE - 0x0100 ) ;
 NVRAM_set_lword ( nvram , 0xD4 , NVRAM_END - NVRAM_CONFSIZE ) ;
 NVRAM_set_lword ( nvram , 0xD8 , NVRAM_CONFSIZE ) ;
 NVRAM_set_lword ( nvram , 0xE8 , NVRAM_END - NVRAM_CONFSIZE - NVRAM_OSAREA_SIZE ) ;
 NVRAM_set_lword ( nvram , 0xEC , NVRAM_OSAREA_SIZE ) ;
 NVRAM_set_crc ( nvram , 0x04 , 0x00 , NVRAM_END - NVRAM_CONFSIZE - NVRAM_OSAREA_SIZE ) ;
 NVRAM_set_crc ( nvram , 0x06 , NVRAM_END - NVRAM_CONFSIZE , NVRAM_CONFSIZE ) ;
 }