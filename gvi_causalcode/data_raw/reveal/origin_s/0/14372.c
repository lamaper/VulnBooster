static bool intel_pt_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 if ( env -> msr_rtit_ctrl || env -> msr_rtit_status || env -> msr_rtit_output_base || env -> msr_rtit_output_mask || env -> msr_rtit_cr3_match ) {
 return true ;
 }
 for ( i = 0 ;
 i < MAX_RTIT_ADDRS ;
 i ++ ) {
 if ( env -> msr_rtit_addrs [ i ] ) {
 return true ;
 }
 }
 return false ;
 }