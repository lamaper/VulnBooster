static uint64_t translate_prom_address ( void * opaque , uint64_t addr ) {
 hwaddr * base_addr = ( hwaddr * ) opaque ;
 return addr + * base_addr - PROM_VADDR ;
 }