static uint32_t vmport_cmd_get_version ( void * opaque , uint32_t addr ) {
 X86CPU * cpu = X86_CPU ( current_cpu ) ;
 cpu -> env . regs [ R_EBX ] = VMPORT_MAGIC ;
 return 6 ;
 }