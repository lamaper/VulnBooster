static uint32_t pmac_ide_readw ( void * opaque , hwaddr addr ) {
 uint16_t retval ;
 MACIOIDEState * d = opaque ;
 addr = ( addr & 0xFFF ) >> 4 ;
 if ( addr == 0 ) {
 retval = ide_data_readw ( & d -> bus , 0 ) ;
 }
 else {
 retval = 0xFFFF ;
 }
 retval = bswap16 ( retval ) ;
 return retval ;
 }