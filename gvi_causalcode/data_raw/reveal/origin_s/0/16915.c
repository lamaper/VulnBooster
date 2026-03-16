static bool xss_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> xss != 0 ;
 }