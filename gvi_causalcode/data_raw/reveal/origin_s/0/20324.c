static int kvm_put_msr_feature_control ( X86CPU * cpu ) {
 int ret ;
 if ( ! has_msr_feature_control ) {
 return 0 ;
 }
 ret = kvm_put_one_msr ( cpu , MSR_IA32_FEATURE_CONTROL , cpu -> env . msr_ia32_feature_control ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 assert ( ret == 1 ) ;
 return 0 ;
 }