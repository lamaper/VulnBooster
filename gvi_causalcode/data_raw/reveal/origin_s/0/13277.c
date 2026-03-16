static bool is_abs_modrm ( uint8_t modrm ) {
 return ( modrm & 0xc7 ) == 0x05 ;
 }