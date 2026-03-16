static bool hyperv_runtime_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 if ( ! cpu -> hyperv_runtime ) {
 return false ;
 }
 return env -> msr_hv_runtime != 0 ;
 }