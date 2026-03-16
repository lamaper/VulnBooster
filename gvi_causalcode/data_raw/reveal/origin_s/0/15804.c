static int kvm_put_debugregs ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 struct kvm_debugregs dbgregs ;
 int i ;
 if ( ! kvm_has_debugregs ( ) ) {
 return 0 ;
 }
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 dbgregs . db [ i ] = env -> dr [ i ] ;
 }
 dbgregs . dr6 = env -> dr [ 6 ] ;
 dbgregs . dr7 = env -> dr [ 7 ] ;
 dbgregs . flags = 0 ;
 return kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_SET_DEBUGREGS , & dbgregs ) ;
 }