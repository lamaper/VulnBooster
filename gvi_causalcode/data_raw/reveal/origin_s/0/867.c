static void PREP_io_800_writeb ( void * opaque , uint32_t addr , uint32_t val ) {
 PPC_IO_DPRINTF ( "0x%08x => 0x%08x\n" , addr - PPC_IO_BASE , val ) ;
 switch ( addr ) {
 case 0x0092 : if ( val & 0x80 ) {
 printf ( "Soft reset asked... Stop emulation\n" ) ;
 abort ( ) ;
 }
 if ( val & 0x40 ) {
 printf ( "Little Endian mode isn't supported (yet ?)\n" ) ;
 abort ( ) ;
 }
 break ;
 case 0x0808 : break ;
 case 0x0810 : NVRAM_lock ^= 0x01 ;
 break ;
 case 0x0812 : NVRAM_lock ^= 0x02 ;
 break ;
 case 0x0814 : break ;
 case 0x081C : syscontrol = val ;
 break ;
 case 0x0850 : if ( val & 0x80 ) {
 printf ( "No support for non-continuous I/O map mode\n" ) ;
 abort ( ) ;
 }
 break ;
 default : break ;
 }
 }