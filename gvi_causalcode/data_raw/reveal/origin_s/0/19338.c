static int kvm_put_fpu ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 struct kvm_fpu fpu ;
 int i ;
 memset ( & fpu , 0 , sizeof fpu ) ;
 fpu . fsw = env -> fpus & ~ ( 7 << 11 ) ;
 fpu . fsw |= ( env -> fpstt & 7 ) << 11 ;
 fpu . fcw = env -> fpuc ;
 fpu . last_opcode = env -> fpop ;
 fpu . last_ip = env -> fpip ;
 fpu . last_dp = env -> fpdp ;
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 fpu . ftwx |= ( ! env -> fptags [ i ] ) << i ;
 }
 memcpy ( fpu . fpr , env -> fpregs , sizeof env -> fpregs ) ;
 for ( i = 0 ;
 i < CPU_NB_REGS ;
 i ++ ) {
 stq_p ( & fpu . xmm [ i ] [ 0 ] , env -> xmm_regs [ i ] . ZMM_Q ( 0 ) ) ;
 stq_p ( & fpu . xmm [ i ] [ 8 ] , env -> xmm_regs [ i ] . ZMM_Q ( 1 ) ) ;
 }
 fpu . mxcsr = env -> mxcsr ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_SET_FPU , & fpu ) ;
 }