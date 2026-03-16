static uint32_t PREP_io_800_readb ( void * opaque , uint32_t addr ) {
 uint32_t retval = 0xFF ;
 switch ( addr ) {
 case 0x0092 : retval = 0x40 ;
 break ;
 case 0x080C : retval = 0xFC ;
 break ;
 case 0x0818 : retval = 0x00 ;
 break ;
 case 0x081C : retval = syscontrol ;
 break ;
 case 0x0823 : retval = 0x03 ;
 break ;
 case 0x0850 : retval = 0x00 ;
 break ;
 default : break ;
 }
 PPC_IO_DPRINTF ( "0x%08x <= 0x%08x\n" , addr - PPC_IO_BASE , retval ) ;
 return retval ;
 }