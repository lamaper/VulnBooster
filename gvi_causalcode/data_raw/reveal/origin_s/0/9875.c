static uint64_t translate_kernel_address ( void * opaque , uint64_t addr ) {
 return addr - 0xf0000000ULL ;
 }