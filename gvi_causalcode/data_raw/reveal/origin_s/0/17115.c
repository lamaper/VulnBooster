static int kvm_inject_mce_oldstyle ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 if ( ! kvm_has_vcpu_events ( ) && env -> exception_injected == EXCP12_MCHK ) {
 unsigned int bank , bank_num = env -> mcg_cap & 0xff ;
 struct kvm_x86_mce mce ;
 env -> exception_injected = - 1 ;
 for ( bank = 0 ;
 bank < bank_num ;
 bank ++ ) {
 if ( env -> mce_banks [ bank * 4 + 1 ] & MCI_STATUS_VAL ) {
 break ;
 }
 }
 assert ( bank < bank_num ) ;
 mce . bank = bank ;
 mce . status = env -> mce_banks [ bank * 4 + 1 ] ;
 mce . mcg_status = env -> mcg_status ;
 mce . addr = env -> mce_banks [ bank * 4 + 2 ] ;
 mce . misc = env -> mce_banks [ bank * 4 + 3 ] ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_X86_SET_MCE , & mce ) ;
 }
 return 0 ;
 }