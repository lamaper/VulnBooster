static bool hyperv_reenlightenment_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_hv_reenlightenment_control != 0 || env -> msr_hv_tsc_emulation_control != 0 || env -> msr_hv_tsc_emulation_status != 0 ;
 }