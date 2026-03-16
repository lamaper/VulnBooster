static void PREP_io_write ( void * opaque , uint32_t addr , uint32_t val ) {
 PPC_IO_DPRINTF ( "0x%08x => 0x%08x\n" , addr - PPC_IO_BASE , val ) ;
 PREP_fake_io [ addr - 0x0398 ] = val ;
 }