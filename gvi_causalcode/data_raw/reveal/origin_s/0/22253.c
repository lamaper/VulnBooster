static struct kvm_cpuid2 * try_get_cpuid ( KVMState * s , int max ) {
 struct kvm_cpuid2 * cpuid ;
 int r , size ;
 size = sizeof ( * cpuid ) + max * sizeof ( * cpuid -> entries ) ;
 cpuid = g_malloc0 ( size ) ;
 cpuid -> nent = max ;
 r = kvm_ioctl ( s , KVM_GET_SUPPORTED_CPUID , cpuid ) ;
 if ( r == 0 && cpuid -> nent >= max ) {
 r = - E2BIG ;
 }
 if ( r < 0 ) {
 if ( r == - E2BIG ) {
 g_free ( cpuid ) ;
 return NULL ;
 }
 else {
 fprintf ( stderr , "KVM_GET_SUPPORTED_CPUID failed: %s\n" , strerror ( - r ) ) ;
 exit ( 1 ) ;
 }
 }
 return cpuid ;
 }