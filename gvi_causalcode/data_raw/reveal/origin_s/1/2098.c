static void vmport_ioport_write ( void * opaque , hwaddr addr , uint64_t val , unsigned size ) {
 CPUX86State * env = cpu_single_env ;
 env -> regs [ R_EAX ] = vmport_ioport_read ( opaque , addr , 4 ) ;
 }