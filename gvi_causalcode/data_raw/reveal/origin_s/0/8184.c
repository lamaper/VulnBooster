static bool tsc_adjust_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> tsc_adjust != 0 ;
 }