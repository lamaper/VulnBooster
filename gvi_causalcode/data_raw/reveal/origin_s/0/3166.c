static bool spec_ctrl_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> spec_ctrl != 0 ;
 }