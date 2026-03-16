static bool virt_ssbd_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> virt_ssbd != 0 ;
 }