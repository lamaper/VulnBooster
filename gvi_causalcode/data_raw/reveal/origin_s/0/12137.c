static uint32_t PREP_io_read ( void * opaque , uint32_t addr ) {
 PPC_IO_DPRINTF ( "0x%08x <= 0x%08x\n" , addr - PPC_IO_BASE , PREP_fake_io [ addr - 0x0398 ] ) ;
 return PREP_fake_io [ addr - 0x0398 ] ;
 }