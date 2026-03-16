uint32_t kvm_arch_get_supported_cpuid ( KVMState * s , uint32_t function , uint32_t index , int reg ) {
 struct kvm_cpuid2 * cpuid ;
 uint32_t ret = 0 ;
 uint32_t cpuid_1_edx ;
 bool found = false ;
 cpuid = get_supported_cpuid ( s ) ;
 struct kvm_cpuid_entry2 * entry = cpuid_find_entry ( cpuid , function , index ) ;
 if ( entry ) {
 found = true ;
 ret = cpuid_entry_get_reg ( entry , reg ) ;
 }
 if ( function == 1 && reg == R_EDX ) {
 ret |= CPUID_MTRR | CPUID_PAT | CPUID_MCE | CPUID_MCA ;
 }
 else if ( function == 1 && reg == R_ECX ) {
 ret |= CPUID_EXT_HYPERVISOR ;
 if ( kvm_irqchip_in_kernel ( ) && kvm_check_extension ( s , KVM_CAP_TSC_DEADLINE_TIMER ) ) {
 ret |= CPUID_EXT_TSC_DEADLINE_TIMER ;
 }
 if ( ! kvm_irqchip_in_kernel ( ) ) {
 ret &= ~ CPUID_EXT_X2APIC ;
 }
 }
 else if ( function == 6 && reg == R_EAX ) {
 ret |= CPUID_6_EAX_ARAT ;
 }
 else if ( function == 7 && index == 0 && reg == R_EBX ) {
 if ( host_tsx_blacklisted ( ) ) {
 ret &= ~ ( CPUID_7_0_EBX_RTM | CPUID_7_0_EBX_HLE ) ;
 }
 }
 else if ( function == 0x80000001 && reg == R_EDX ) {
 cpuid_1_edx = kvm_arch_get_supported_cpuid ( s , 1 , 0 , R_EDX ) ;
 ret |= cpuid_1_edx & CPUID_EXT2_AMD_ALIASES ;
 }
 else if ( function == KVM_CPUID_FEATURES && reg == R_EAX ) {
 if ( ! kvm_irqchip_in_kernel ( ) ) {
 ret &= ~ ( 1U << KVM_FEATURE_PV_UNHALT ) ;
 }
 }
 else if ( function == KVM_CPUID_FEATURES && reg == R_EDX ) {
 ret |= KVM_HINTS_DEDICATED ;
 found = 1 ;
 }
 if ( ( function == KVM_CPUID_FEATURES ) && ! found ) {
 ret = get_para_features ( s ) ;
 }
 return ret ;
 }