static int kvm_get_debugregs ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 struct kvm_debugregs dbgregs ;
 int i , ret ;
 if ( ! kvm_has_debugregs ( ) ) {
 return 0 ;
 }
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_DEBUGREGS , & dbgregs ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 for ( i = 0 ;
 i < 4 ;
 i ++ ) {
 env -> dr [ i ] = dbgregs . db [ i ] ;
 }
 env -> dr [ 4 ] = env -> dr [ 6 ] = dbgregs . dr6 ;
 env -> dr [ 5 ] = env -> dr [ 7 ] = dbgregs . dr7 ;
 return 0 ;
 }