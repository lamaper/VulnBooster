static bool hyperv_crash_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 for ( i = 0 ;
 i < HV_CRASH_PARAMS ;
 i ++ ) {
 if ( env -> msr_hv_crash_params [ i ] ) {
 return true ;
 }
 }
 return false ;
 }