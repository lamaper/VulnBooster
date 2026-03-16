static void NVRAM_set_crc ( m48t59_t * nvram , uint32_t addr , uint32_t start , uint32_t count ) {
 uint32_t i ;
 uint16_t crc = 0xFFFF ;
 int odd = 0 ;
 if ( count & 1 ) odd = 1 ;
 count &= ~ 1 ;
 for ( i = 0 ;
 i != count ;
 i ++ ) {
 crc = NVRAM_crc_update ( crc , NVRAM_get_word ( nvram , start + i ) ) ;
 }
 if ( odd ) {
 crc = NVRAM_crc_update ( crc , NVRAM_get_byte ( nvram , start + i ) << 8 ) ;
 }
 NVRAM_set_word ( nvram , addr , crc ) ;
 }