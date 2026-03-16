static uint32_t PPC_io_readb ( target_phys_addr_t addr ) {
 uint32_t ret = cpu_inb ( NULL , addr - PPC_IO_BASE ) ;

 PPC_IO_DPRINTF ( "0x%08x <= 0x%02x\n" , addr - PPC_IO_BASE , ret ) ;
 }
 return ret ;
 }