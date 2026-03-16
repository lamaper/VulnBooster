static int hyperv_handle_properties ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 if ( cpu -> hyperv_relaxed_timing ) {
 env -> features [ FEAT_HYPERV_EAX ] |= HV_HYPERCALL_AVAILABLE ;
 }
 if ( cpu -> hyperv_vapic ) {
 env -> features [ FEAT_HYPERV_EAX ] |= HV_HYPERCALL_AVAILABLE ;
 env -> features [ FEAT_HYPERV_EAX ] |= HV_APIC_ACCESS_AVAILABLE ;
 }
 if ( cpu -> hyperv_time ) {
 if ( kvm_check_extension ( cs -> kvm_state , KVM_CAP_HYPERV_TIME ) <= 0 ) {
 fprintf ( stderr , "Hyper-V clocksources " "(requested by 'hv-time' cpu flag) " "are not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_HYPERCALL_AVAILABLE ;
 env -> features [ FEAT_HYPERV_EAX ] |= HV_TIME_REF_COUNT_AVAILABLE ;
 env -> features [ FEAT_HYPERV_EAX ] |= HV_REFERENCE_TSC_AVAILABLE ;
 }
 if ( cpu -> hyperv_frequencies ) {
 if ( ! has_msr_hv_frequencies ) {
 fprintf ( stderr , "Hyper-V frequency MSRs " "(requested by 'hv-frequencies' cpu flag) " "are not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_ACCESS_FREQUENCY_MSRS ;
 env -> features [ FEAT_HYPERV_EDX ] |= HV_FREQUENCY_MSRS_AVAILABLE ;
 }
 if ( cpu -> hyperv_crash ) {
 if ( ! has_msr_hv_crash ) {
 fprintf ( stderr , "Hyper-V crash MSRs " "(requested by 'hv-crash' cpu flag) " "are not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EDX ] |= HV_GUEST_CRASH_MSR_AVAILABLE ;
 }
 if ( cpu -> hyperv_reenlightenment ) {
 if ( ! has_msr_hv_reenlightenment ) {
 fprintf ( stderr , "Hyper-V Reenlightenment MSRs " "(requested by 'hv-reenlightenment' cpu flag) " "are not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_ACCESS_REENLIGHTENMENTS_CONTROL ;
 }
 env -> features [ FEAT_HYPERV_EDX ] |= HV_CPU_DYNAMIC_PARTITIONING_AVAILABLE ;
 if ( cpu -> hyperv_reset ) {
 if ( ! has_msr_hv_reset ) {
 fprintf ( stderr , "Hyper-V reset MSR " "(requested by 'hv-reset' cpu flag) " "is not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_RESET_AVAILABLE ;
 }
 if ( cpu -> hyperv_vpindex ) {
 if ( ! has_msr_hv_vpindex ) {
 fprintf ( stderr , "Hyper-V VP_INDEX MSR " "(requested by 'hv-vpindex' cpu flag) " "is not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_VP_INDEX_AVAILABLE ;
 }
 if ( cpu -> hyperv_runtime ) {
 if ( ! has_msr_hv_runtime ) {
 fprintf ( stderr , "Hyper-V VP_RUNTIME MSR " "(requested by 'hv-runtime' cpu flag) " "is not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_VP_RUNTIME_AVAILABLE ;
 }
 if ( cpu -> hyperv_synic ) {
 if ( ! has_msr_hv_synic || kvm_vcpu_enable_cap ( cs , KVM_CAP_HYPERV_SYNIC , 0 ) ) {
 fprintf ( stderr , "Hyper-V SynIC is not supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_SYNIC_AVAILABLE ;
 }
 if ( cpu -> hyperv_stimer ) {
 if ( ! has_msr_hv_stimer ) {
 fprintf ( stderr , "Hyper-V timers aren't supported by kernel\n" ) ;
 return - ENOSYS ;
 }
 env -> features [ FEAT_HYPERV_EAX ] |= HV_SYNTIMERS_AVAILABLE ;
 }
 return 0 ;
 }