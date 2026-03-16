static uint16_t NVRAM_crc_update ( uint16_t prev , uint16_t value ) {
 uint16_t tmp ;
 uint16_t pd , pd1 , pd2 ;
 tmp = prev >> 8 ;
 pd = prev ^ value ;
 pd1 = pd & 0x000F ;
 pd2 = ( ( pd >> 4 ) & 0x000F ) ^ pd1 ;
 tmp ^= ( pd1 << 3 ) | ( pd1 << 8 ) ;
 tmp ^= pd2 | ( pd2 << 7 ) | ( pd2 << 12 ) ;
 return tmp ;
 }