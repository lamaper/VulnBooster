static int kvm_get_xsave ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 X86XSaveArea * xsave = env -> kvm_xsave_buf ;
 int ret ;
 if ( ! has_xsave ) {
 return kvm_get_fpu ( cpu ) ;
 }
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_XSAVE , xsave ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 x86_cpu_xrstor_all_areas ( cpu , xsave ) ;
 return 0 ;
 }