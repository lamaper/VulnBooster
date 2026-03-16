static bool hyperv_vapic_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_hv_vapic != 0 ;
 }