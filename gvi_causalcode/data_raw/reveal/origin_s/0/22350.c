static uint32_t PREP_io_800_readb ( void * opaque , uint32_t addr ) {
 sysctrl_t * sysctrl = opaque ;
 uint32_t retval = 0xFF ;
 switch ( addr ) {
 case 0x0092 : retval = sysctrl -> endian << 1 ;
 break ;
 case 0x0800 : retval = 0xEF ;
 break ;
 case 0x0802 : retval = 0xAD ;
 break ;
 case 0x0803 : retval = 0xE0 ;
 break ;
 case 0x080C : retval = 0x3C ;
 break ;
 case 0x0810 : retval = 0x39 ;
 break ;
 case 0x0814 : break ;
 case 0x0818 : retval = 0x00 ;
 break ;
 case 0x081C : retval = sysctrl -> syscontrol ;
 break ;
 case 0x0823 : retval = 0x03 ;
 break ;
 case 0x0850 : retval = sysctrl -> contiguous_map ;
 break ;
 default : printf ( "ERROR: unaffected IO port: %04" PRIx32 " read\n" , addr ) ;
 break ;
 }
 PPC_IO_DPRINTF ( "0x%08" PRIx32 " <= 0x%02" PRIx32 "\n" , addr - PPC_IO_BASE , retval ) ;
 return retval ;
 }