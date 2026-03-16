static int kvm_put_xsave ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 X86XSaveArea * xsave = env -> kvm_xsave_buf ;
 if ( ! has_xsave ) {
 return kvm_put_fpu ( cpu ) ;
 }
 x86_cpu_xsave_all_areas ( cpu , xsave ) ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_SET_XSAVE , xsave ) ;
 }