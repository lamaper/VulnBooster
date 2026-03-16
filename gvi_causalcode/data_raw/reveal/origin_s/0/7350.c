static void vmport_ioport_write ( void * opaque , hwaddr addr , uint64_t val , unsigned size ) {
 X86CPU * cpu = X86_CPU ( current_cpu ) ;
 cpu -> env . regs [ R_EAX ] = vmport_ioport_read ( opaque , addr , 4 ) ;
 }