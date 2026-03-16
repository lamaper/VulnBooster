static bool hyperv_synic_enable_needed ( void * opaque ) {
 X86CPU * cpu = opaque ;
 CPUX86State * env = & cpu -> env ;
 int i ;
 if ( env -> msr_hv_synic_control != 0 || env -> msr_hv_synic_evt_page != 0 || env -> msr_hv_synic_msg_page != 0 ) {
 return true ;
 }
 for ( i = 0 ;
 i < ARRAY_SIZE ( env -> msr_hv_synic_sint ) ;
 i ++ ) {
 if ( env -> msr_hv_synic_sint [ i ] != 0 ) {
 return true ;
 }
 }
 return false ;
 }