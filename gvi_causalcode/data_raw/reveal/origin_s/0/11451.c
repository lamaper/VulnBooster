bool kvm_arch_stop_on_emulation_error ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 kvm_cpu_synchronize_state ( cs ) ;
 return ! ( env -> cr [ 0 ] & CR0_PE_MASK ) || ( ( env -> segs [ R_CS ] . selector & 3 ) != 3 ) ;
 }