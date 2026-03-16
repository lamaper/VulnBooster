static struct kvm_cpuid2 * get_supported_cpuid ( KVMState * s ) {
 struct kvm_cpuid2 * cpuid ;
 int max = 1 ;
 if ( cpuid_cache != NULL ) {
 return cpuid_cache ;
 }
 while ( ( cpuid = try_get_cpuid ( s , max ) ) == NULL ) {
 max *= 2 ;
 }
 cpuid_cache = cpuid ;
 return cpuid ;
 }