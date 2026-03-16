static bool hyperv_time_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_hv_tsc != 0 ;
 }