static uint32_t PPC_io_readl ( target_phys_addr_t addr ) {
 uint32_t ret = cpu_inl ( NULL , addr - PPC_IO_BASE ) ;


 return ret ;
 }