static bool hyperv_stimer_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( env -> msr_hv_stimer_config ) ;
 i ++ ) {
 if ( env -> msr_hv_stimer_config [ i ] || env -> msr_hv_stimer_count [ i ] ) {
 return true ;
 }
 }
 return false ;
 }