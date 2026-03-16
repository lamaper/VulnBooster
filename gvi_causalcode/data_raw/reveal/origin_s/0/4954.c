static void PPC_prep_io_writeb ( void * opaque , hwaddr addr , uint32_t value ) {
 sysctrl_t * sysctrl = opaque ;
 addr = prep_IO_address ( sysctrl , addr ) ;
 cpu_outb ( addr , value ) ;
 }