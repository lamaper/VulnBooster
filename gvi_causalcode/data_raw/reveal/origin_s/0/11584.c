static uint32_t PPC_io_readw ( target_phys_addr_t addr ) {
 uint32_t ret = cpu_inw ( NULL , addr - PPC_IO_BASE ) ;


 PPC_IO_DPRINTF ( "0x%08x <= 0x%04x\n" , addr - PPC_IO_BASE , ret ) ;
 }
 return ret ;
 }