static uint64_t vmport_ioport_read ( void * opaque , hwaddr addr , unsigned size ) {
 VMPortState * s = opaque ;
 CPUX86State * env = cpu_single_env ;
 unsigned char command ;
 uint32_t eax ;
 cpu_synchronize_state ( CPU ( x86_env_get_cpu ( env ) ) ) ;
 eax = env -> regs [ R_EAX ] ;
 if ( eax != VMPORT_MAGIC ) return eax ;
 command = env -> regs [ R_ECX ] ;
 if ( command >= VMPORT_ENTRIES ) return eax ;
 if ( ! s -> func [ command ] ) {


 }
 return s -> func [ command ] ( s -> opaque [ command ] , addr ) ;
 }