static uint32_t vmport_cmd_ram_size ( void * opaque , uint32_t addr ) {
 CPUX86State * env = cpu_single_env ;
 env -> regs [ R_EBX ] = 0x1177 ;
 return ram_size ;
 }