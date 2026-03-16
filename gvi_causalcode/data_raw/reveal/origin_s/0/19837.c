static uint32_t PPC_prep_io_readb ( void * opaque , hwaddr addr ) {
 sysctrl_t * sysctrl = opaque ;
 uint32_t ret ;
 addr = prep_IO_address ( sysctrl , addr ) ;
 ret = cpu_inb ( addr ) ;
 return ret ;
 }