static bool tscdeadline_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> tsc_deadline != 0 ;
 }