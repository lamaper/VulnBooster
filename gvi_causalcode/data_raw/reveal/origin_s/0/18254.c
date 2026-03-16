void vmmouse_get_data ( uint32_t * data ) {
 X86CPU * cpu = X86_CPU ( current_cpu ) ;
 CPUX86State * env = & cpu -> env ;
 data [ 0 ] = env -> regs [ R_EAX ] ;
 data [ 1 ] = env -> regs [ R_EBX ] ;
 data [ 2 ] = env -> regs [ R_ECX ] ;
 data [ 3 ] = env -> regs [ R_EDX ] ;
 data [ 4 ] = env -> regs [ R_ESI ] ;
 data [ 5 ] = env -> regs [ R_EDI ] ;
 }