static bool misc_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 return env -> msr_ia32_misc_enable != MSR_IA32_MISC_ENABLE_DEFAULT ;
 }