static int kvm_get_tsc ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 struct {
 struct kvm_msrs info ;
 struct kvm_msr_entry entries [ 1 ] ;
 }
 msr_data ;
 int ret ;
 if ( env -> tsc_valid ) {
 return 0 ;
 }
 msr_data . info . nmsrs = 1 ;
 msr_data . entries [ 0 ] . index = MSR_IA32_TSC ;
 env -> tsc_valid = ! runstate_is_running ( ) ;
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_MSRS , & msr_data ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 assert ( ret == 1 ) ;
 env -> tsc = msr_data . entries [ 0 ] . data ;
 return 0 ;
 }