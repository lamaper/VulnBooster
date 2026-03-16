static uint64_t vmport_ioport_read ( void * opaque , hwaddr addr , unsigned size ) {
 VMPortState * s = opaque ;
 CPUState * cs = current_cpu ;
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 unsigned char command ;
 uint32_t eax ;
 cpu_synchronize_state ( cs ) ;
 eax = env -> regs [ R_EAX ] ;
 if ( eax != VMPORT_MAGIC ) return eax ;
 command = env -> regs [ R_ECX ] ;
 if ( command >= VMPORT_ENTRIES ) return eax ;
 if ( ! s -> func [ command ] ) {


 }
 return s -> func [ command ] ( s -> opaque [ command ] , addr ) ;
 }