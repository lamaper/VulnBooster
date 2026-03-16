static void PPC_io_writeb ( target_phys_addr_t addr , uint32_t value ) {

 PPC_IO_DPRINTF ( "0x%08x => 0x%02x\n" , addr - PPC_IO_BASE , value ) ;
 }
 cpu_outb ( NULL , addr - PPC_IO_BASE , value ) ;
 }