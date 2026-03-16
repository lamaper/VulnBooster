int kvm_arch_init_vcpu ( CPUState * cs ) {
 struct {
 struct kvm_cpuid2 cpuid ;
 struct kvm_cpuid_entry2 entries [ KVM_MAX_CPUID_ENTRIES ] ;
 }
 QEMU_PACKED cpuid_data ;
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 uint32_t limit , i , j , cpuid_i ;
 uint32_t unused ;
 struct kvm_cpuid_entry2 * c ;
 uint32_t signature [ 3 ] ;
 int kvm_base = KVM_CPUID_SIGNATURE ;
 int r ;
 Error * local_err = NULL ;
 memset ( & cpuid_data , 0 , sizeof ( cpuid_data ) ) ;
 cpuid_i = 0 ;
 r = kvm_arch_set_tsc_khz ( cs ) ;
 if ( r < 0 ) {
 goto fail ;
 }
 if ( ! env -> tsc_khz ) {
 r = kvm_check_extension ( cs -> kvm_state , KVM_CAP_GET_TSC_KHZ ) ? kvm_vcpu_ioctl ( cs , KVM_GET_TSC_KHZ ) : - ENOTSUP ;
 if ( r > 0 ) {
 env -> tsc_khz = r ;
 }
 }
 if ( hyperv_enabled ( cpu ) ) {
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_VENDOR_AND_MAX_FUNCTIONS ;
 if ( ! cpu -> hyperv_vendor_id ) {
 memcpy ( signature , "Microsoft Hv" , 12 ) ;
 }
 else {
 size_t len = strlen ( cpu -> hyperv_vendor_id ) ;
 if ( len > 12 ) {
 error_report ( "hv-vendor-id truncated to 12 characters" ) ;
 len = 12 ;
 }
 memset ( signature , 0 , 12 ) ;
 memcpy ( signature , cpu -> hyperv_vendor_id , len ) ;
 }
 c -> eax = HV_CPUID_MIN ;
 c -> ebx = signature [ 0 ] ;
 c -> ecx = signature [ 1 ] ;
 c -> edx = signature [ 2 ] ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_INTERFACE ;
 memcpy ( signature , "Hv#1\0\0\0\0\0\0\0\0" , 12 ) ;
 c -> eax = signature [ 0 ] ;
 c -> ebx = 0 ;
 c -> ecx = 0 ;
 c -> edx = 0 ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_VERSION ;
 c -> eax = 0x00001bbc ;
 c -> ebx = 0x00060001 ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_FEATURES ;
 r = hyperv_handle_properties ( cs ) ;
 if ( r ) {
 return r ;
 }
 c -> eax = env -> features [ FEAT_HYPERV_EAX ] ;
 c -> ebx = env -> features [ FEAT_HYPERV_EBX ] ;
 c -> edx = env -> features [ FEAT_HYPERV_EDX ] ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_ENLIGHTMENT_INFO ;
 if ( cpu -> hyperv_relaxed_timing ) {
 c -> eax |= HV_RELAXED_TIMING_RECOMMENDED ;
 }
 if ( cpu -> hyperv_vapic ) {
 c -> eax |= HV_APIC_ACCESS_RECOMMENDED ;
 }
 c -> ebx = cpu -> hyperv_spinlock_attempts ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = HV_CPUID_IMPLEMENT_LIMITS ;
 c -> eax = cpu -> hv_max_vps ;
 c -> ebx = 0x40 ;
 kvm_base = KVM_CPUID_SIGNATURE_NEXT ;
 has_msr_hv_hypercall = true ;
 }
 if ( cpu -> expose_kvm ) {
 memcpy ( signature , "KVMKVMKVM\0\0\0" , 12 ) ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = KVM_CPUID_SIGNATURE | kvm_base ;
 c -> eax = KVM_CPUID_FEATURES | kvm_base ;
 c -> ebx = signature [ 0 ] ;
 c -> ecx = signature [ 1 ] ;
 c -> edx = signature [ 2 ] ;
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = KVM_CPUID_FEATURES | kvm_base ;
 c -> eax = env -> features [ FEAT_KVM ] ;
 c -> edx = env -> features [ FEAT_KVM_HINTS ] ;
 }
 cpu_x86_cpuid ( env , 0 , 0 , & limit , & unused , & unused , & unused ) ;
 for ( i = 0 ;
 i <= limit ;
 i ++ ) {
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "unsupported level value: 0x%x\n" , limit ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 switch ( i ) {
 case 2 : {
 int times ;
 c -> function = i ;
 c -> flags = KVM_CPUID_FLAG_STATEFUL_FUNC | KVM_CPUID_FLAG_STATE_READ_NEXT ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 times = c -> eax & 0xff ;
 for ( j = 1 ;
 j < times ;
 ++ j ) {
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "cpuid_data is full, no space for " "cpuid(eax:2):eax & 0xf = 0x%x\n" , times ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = i ;
 c -> flags = KVM_CPUID_FLAG_STATEFUL_FUNC ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 }
 break ;
 }
 case 4 : case 0xb : case 0xd : for ( j = 0 ;
 ;
 j ++ ) {
 if ( i == 0xd && j == 64 ) {
 break ;
 }
 c -> function = i ;
 c -> flags = KVM_CPUID_FLAG_SIGNIFCANT_INDEX ;
 c -> index = j ;
 cpu_x86_cpuid ( env , i , j , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 if ( i == 4 && c -> eax == 0 ) {
 break ;
 }
 if ( i == 0xb && ! ( c -> ecx & 0xff00 ) ) {
 break ;
 }
 if ( i == 0xd && c -> eax == 0 ) {
 continue ;
 }
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "cpuid_data is full, no space for " "cpuid(eax:0x%x,ecx:0x%x)\n" , i , j ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 }
 break ;
 case 0x14 : {
 uint32_t times ;
 c -> function = i ;
 c -> index = 0 ;
 c -> flags = KVM_CPUID_FLAG_SIGNIFCANT_INDEX ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 times = c -> eax ;
 for ( j = 1 ;
 j <= times ;
 ++ j ) {
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "cpuid_data is full, no space for " "cpuid(eax:0x14,ecx:0x%x)\n" , j ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = i ;
 c -> index = j ;
 c -> flags = KVM_CPUID_FLAG_SIGNIFCANT_INDEX ;
 cpu_x86_cpuid ( env , i , j , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 }
 break ;
 }
 default : c -> function = i ;
 c -> flags = 0 ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 break ;
 }
 }
 if ( limit >= 0x0a ) {
 uint32_t eax , edx ;
 cpu_x86_cpuid ( env , 0x0a , 0 , & eax , & unused , & unused , & edx ) ;
 has_architectural_pmu_version = eax & 0xff ;
 if ( has_architectural_pmu_version > 0 ) {
 num_architectural_pmu_gp_counters = ( eax & 0xff00 ) >> 8 ;
 if ( num_architectural_pmu_gp_counters > MAX_GP_COUNTERS ) {
 num_architectural_pmu_gp_counters = MAX_GP_COUNTERS ;
 }
 if ( has_architectural_pmu_version > 1 ) {
 num_architectural_pmu_fixed_counters = edx & 0x1f ;
 if ( num_architectural_pmu_fixed_counters > MAX_FIXED_COUNTERS ) {
 num_architectural_pmu_fixed_counters = MAX_FIXED_COUNTERS ;
 }
 }
 }
 }
 cpu_x86_cpuid ( env , 0x80000000 , 0 , & limit , & unused , & unused , & unused ) ;
 for ( i = 0x80000000 ;
 i <= limit ;
 i ++ ) {
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "unsupported xlevel value: 0x%x\n" , limit ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = i ;
 c -> flags = 0 ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 }
 if ( env -> cpuid_xlevel2 > 0 ) {
 cpu_x86_cpuid ( env , 0xC0000000 , 0 , & limit , & unused , & unused , & unused ) ;
 for ( i = 0xC0000000 ;
 i <= limit ;
 i ++ ) {
 if ( cpuid_i == KVM_MAX_CPUID_ENTRIES ) {
 fprintf ( stderr , "unsupported xlevel2 value: 0x%x\n" , limit ) ;
 abort ( ) ;
 }
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = i ;
 c -> flags = 0 ;
 cpu_x86_cpuid ( env , i , 0 , & c -> eax , & c -> ebx , & c -> ecx , & c -> edx ) ;
 }
 }
 cpuid_data . cpuid . nent = cpuid_i ;
 if ( ( ( env -> cpuid_version >> 8 ) & 0xF ) >= 6 && ( env -> features [ FEAT_1_EDX ] & ( CPUID_MCE | CPUID_MCA ) ) == ( CPUID_MCE | CPUID_MCA ) && kvm_check_extension ( cs -> kvm_state , KVM_CAP_MCE ) > 0 ) {
 uint64_t mcg_cap , unsupported_caps ;
 int banks ;
 int ret ;
 ret = kvm_get_mce_cap_supported ( cs -> kvm_state , & mcg_cap , & banks ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "kvm_get_mce_cap_supported: %s" , strerror ( - ret ) ) ;
 return ret ;
 }
 if ( banks < ( env -> mcg_cap & MCG_CAP_BANKS_MASK ) ) {
 error_report ( "kvm: Unsupported MCE bank count (QEMU = %d, KVM = %d)" , ( int ) ( env -> mcg_cap & MCG_CAP_BANKS_MASK ) , banks ) ;
 return - ENOTSUP ;
 }
 unsupported_caps = env -> mcg_cap & ~ ( mcg_cap | MCG_CAP_BANKS_MASK ) ;
 if ( unsupported_caps ) {
 if ( unsupported_caps & MCG_LMCE_P ) {
 error_report ( "kvm: LMCE not supported" ) ;
 return - ENOTSUP ;
 }
 warn_report ( "Unsupported MCG_CAP bits: 0x%" PRIx64 , unsupported_caps ) ;
 }
 env -> mcg_cap &= mcg_cap | MCG_CAP_BANKS_MASK ;
 ret = kvm_vcpu_ioctl ( cs , KVM_X86_SETUP_MCE , & env -> mcg_cap ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "KVM_X86_SETUP_MCE: %s" , strerror ( - ret ) ) ;
 return ret ;
 }
 }
 qemu_add_vm_change_state_handler ( cpu_update_state , env ) ;
 c = cpuid_find_entry ( & cpuid_data . cpuid , 1 , 0 ) ;
 if ( c ) {
 has_msr_feature_control = ! ! ( c -> ecx & CPUID_EXT_VMX ) || ! ! ( c -> ecx & CPUID_EXT_SMX ) ;
 }
 if ( env -> mcg_cap & MCG_LMCE_P ) {
 has_msr_mcg_ext_ctl = has_msr_feature_control = true ;
 }
 if ( ! env -> user_tsc_khz ) {
 if ( ( env -> features [ FEAT_8000_0007_EDX ] & CPUID_APM_INVTSC ) && invtsc_mig_blocker == NULL ) {
 error_setg ( & invtsc_mig_blocker , "State blocked by non-migratable CPU device" " (invtsc flag)" ) ;
 r = migrate_add_blocker ( invtsc_mig_blocker , & local_err ) ;
 if ( local_err ) {
 error_report_err ( local_err ) ;
 error_free ( invtsc_mig_blocker ) ;
 goto fail ;
 }
 vmstate_x86_cpu . unmigratable = 1 ;
 }
 }
 if ( cpu -> vmware_cpuid_freq && cpu -> expose_kvm && kvm_base == KVM_CPUID_SIGNATURE && tsc_is_stable_and_known ( env ) ) {
 c = & cpuid_data . entries [ cpuid_i ++ ] ;
 c -> function = KVM_CPUID_SIGNATURE | 0x10 ;
 c -> eax = env -> tsc_khz ;
 c -> ebx = 1000000 ;
 c -> ecx = c -> edx = 0 ;
 c = cpuid_find_entry ( & cpuid_data . cpuid , kvm_base , 0 ) ;
 c -> eax = MAX ( c -> eax , KVM_CPUID_SIGNATURE | 0x10 ) ;
 }
 cpuid_data . cpuid . nent = cpuid_i ;
 cpuid_data . cpuid . padding = 0 ;
 r = kvm_vcpu_ioctl ( cs , KVM_SET_CPUID2 , & cpuid_data ) ;
 if ( r ) {
 goto fail ;
 }
 if ( has_xsave ) {
 env -> kvm_xsave_buf = qemu_memalign ( 4096 , sizeof ( struct kvm_xsave ) ) ;
 }
 cpu -> kvm_msr_buf = g_malloc0 ( MSR_BUF_SIZE ) ;
 if ( ! ( env -> features [ FEAT_8000_0001_EDX ] & CPUID_EXT2_RDTSCP ) ) {
 has_msr_tsc_aux = false ;
 }
 return 0 ;
 fail : migrate_del_blocker ( invtsc_mig_blocker ) ;
 return r ;
 }