static struct kvm_cpuid_entry2 * cpuid_find_entry ( struct kvm_cpuid2 * cpuid , uint32_t function , uint32_t index ) {
 int i ;
 for ( i = 0 ;
 i < cpuid -> nent ;
 ++ i ) {
 if ( cpuid -> entries [ i ] . function == function && cpuid -> entries [ i ] . index == index ) {
 return & cpuid -> entries [ i ] ;
 }
 }
 return NULL ;
 }