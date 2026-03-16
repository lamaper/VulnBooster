static bool msr_smi_count_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_smi_count != 0 ;
 }