static bool feature_control_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_ia32_feature_control != 0 ;
 }