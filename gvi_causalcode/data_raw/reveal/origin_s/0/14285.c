static bool pmu_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 if ( env -> msr_fixed_ctr_ctrl || env -> msr_global_ctrl || env -> msr_global_status || env -> msr_global_ovf_ctrl ) {
 return true ;
 }
 for ( i = 0 ;
 i < MAX_FIXED_COUNTERS ;
 i ++ ) {
 if ( env -> msr_fixed_counters [ i ] ) {
 return true ;
 }
 }
 for ( i = 0 ;
 i < MAX_GP_COUNTERS ;
 i ++ ) {
 if ( env -> msr_gp_counters [ i ] || env -> msr_gp_evtsel [ i ] ) {
 return true ;
 }
 }
 return false ;
 }