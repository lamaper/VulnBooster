static uint32_t vmport_cmd_ram_size ( void * opaque , uint32_t addr ) {
 X86CPU * cpu = X86_CPU ( current_cpu ) ;
 cpu -> env . regs [ R_EBX ] = 0x1177 ;
 return ram_size ;
 }