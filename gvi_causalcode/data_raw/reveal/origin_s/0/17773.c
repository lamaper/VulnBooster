int kvm_arch_process_async_events ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 CPUX86State * env = & cpu -> env ;
 if ( cs -> interrupt_request & CPU_INTERRUPT_MCE ) {
 assert ( env -> mcg_cap ) ;
 cs -> interrupt_request &= ~ CPU_INTERRUPT_MCE ;
 kvm_cpu_synchronize_state ( cs ) ;
 if ( env -> exception_injected == EXCP08_DBLE ) {
 qemu_system_reset_request ( SHUTDOWN_CAUSE_GUEST_RESET ) ;
 cs -> exit_request = 1 ;
 return 0 ;
 }
 env -> exception_injected = EXCP12_MCHK ;
 env -> has_error_code = 0 ;
 cs -> halted = 0 ;
 if ( kvm_irqchip_in_kernel ( ) && env -> mp_state == KVM_MP_STATE_HALTED ) {
 env -> mp_state = KVM_MP_STATE_RUNNABLE ;
 }
 }
 if ( ( cs -> interrupt_request & CPU_INTERRUPT_INIT ) && ! ( env -> hflags & HF_SMM_MASK ) ) {
 kvm_cpu_synchronize_state ( cs ) ;
 do_cpu_init ( cpu ) ;
 }
 if ( kvm_irqchip_in_kernel ( ) ) {
 return 0 ;
 }
 if ( cs -> interrupt_request & CPU_INTERRUPT_POLL ) {
 cs -> interrupt_request &= ~ CPU_INTERRUPT_POLL ;
 apic_poll_irq ( cpu -> apic_state ) ;
 }
 if ( ( ( cs -> interrupt_request & CPU_INTERRUPT_HARD ) && ( env -> eflags & IF_MASK ) ) || ( cs -> interrupt_request & CPU_INTERRUPT_NMI ) ) {
 cs -> halted = 0 ;
 }
 if ( cs -> interrupt_request & CPU_INTERRUPT_SIPI ) {
 kvm_cpu_synchronize_state ( cs ) ;
 do_cpu_sipi ( cpu ) ;
 }
 if ( cs -> interrupt_request & CPU_INTERRUPT_TPR ) {
 cs -> interrupt_request &= ~ CPU_INTERRUPT_TPR ;
 kvm_cpu_synchronize_state ( cs ) ;
 apic_handle_tpr_access_report ( cpu -> apic_state , env -> eip , env -> tpr_access_type ) ;
 }
 return cs -> halted ;
 }