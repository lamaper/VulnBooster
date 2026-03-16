static bool mcg_ext_ctl_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return cpu -> enable_lmce && env -> mcg_ext_ctl ;
 }