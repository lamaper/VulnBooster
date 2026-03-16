static inline hwaddr prep_IO_address ( sysctrl_t * sysctrl , hwaddr addr ) {
 if ( sysctrl -> contiguous_map == 0 ) {
 addr &= 0xFFFF ;
 }
 else {
 addr = ( addr & 0x1F ) | ( ( addr & 0x007FFF000 ) >> 7 ) ;
 }
 return addr ;
 }