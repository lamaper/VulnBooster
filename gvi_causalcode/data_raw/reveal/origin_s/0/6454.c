static bool hyperv_hypercall_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_hv_hypercall != 0 || env -> msr_hv_guest_os_id != 0 ;
 }