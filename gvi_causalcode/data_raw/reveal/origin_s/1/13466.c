static uint32_t vmport_cmd_get_version ( void * opaque , uint32_t addr ) {
 CPUX86State * env = cpu_single_env ;
 env -> regs [ R_EBX ] = VMPORT_MAGIC ;
 return 6 ;
 }