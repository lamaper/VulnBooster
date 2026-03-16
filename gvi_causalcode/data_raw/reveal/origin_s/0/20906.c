static uint32_t cpuid_entry_get_reg ( struct kvm_cpuid_entry2 * entry , int reg ) {
 uint32_t ret = 0 ;
 switch ( reg ) {
 case R_EAX : ret = entry -> eax ;
 break ;
 case R_EBX : ret = entry -> ebx ;
 break ;
 case R_ECX : ret = entry -> ecx ;
 break ;
 case R_EDX : ret = entry -> edx ;
 break ;
 }
 return ret ;
 }