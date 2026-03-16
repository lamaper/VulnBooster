static bool fpop_ip_dp_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> fpop != 0 || env -> fpip != 0 || env -> fpdp != 0 ;
 }