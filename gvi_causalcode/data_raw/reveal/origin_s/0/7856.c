static int kvm_put_tscdeadline_msr ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 int ret ;
 if ( ! has_msr_tsc_deadline ) {
 return 0 ;
 }
 ret = kvm_put_one_msr ( cpu , MSR_IA32_TSCDEADLINE , env -> tsc_deadline ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 assert ( ret == 1 ) ;
 return 0 ;
 }