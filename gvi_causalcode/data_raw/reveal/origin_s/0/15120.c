static void PPC_prep_io_writew ( void * opaque , hwaddr addr , uint32_t value ) {
 sysctrl_t * sysctrl = opaque ;
 addr = prep_IO_address ( sysctrl , addr ) ;
 PPC_IO_DPRINTF ( "0x" TARGET_FMT_plx " => 0x%08" PRIx32 "\n" , addr , value ) ;
 cpu_outw ( addr , value ) ;
 }