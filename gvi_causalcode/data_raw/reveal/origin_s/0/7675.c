static uint32_t PPC_prep_io_readw ( void * opaque , hwaddr addr ) {
 sysctrl_t * sysctrl = opaque ;
 uint32_t ret ;
 addr = prep_IO_address ( sysctrl , addr ) ;
 ret = cpu_inw ( addr ) ;
 PPC_IO_DPRINTF ( "0x" TARGET_FMT_plx " <= 0x%08" PRIx32 "\n" , addr , ret ) ;
 return ret ;
 }