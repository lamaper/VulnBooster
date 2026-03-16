static void PPC_io_writew ( target_phys_addr_t addr , uint32_t value ) {
 if ( ( addr < 0x800001f0 || addr > 0x800001f7 ) && ( addr < 0x80000170 || addr > 0x80000177 ) ) {
 PPC_IO_DPRINTF ( "0x%08x => 0x%04x\n" , addr - PPC_IO_BASE , value ) ;
 }


 }