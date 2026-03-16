int kvm_arch_handle_exit ( CPUState * cs , struct kvm_run * run ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 uint64_t code ;
 int ret ;
 switch ( run -> exit_reason ) {
 case KVM_EXIT_HLT : DPRINTF ( "handle_hlt\n" ) ;
 qemu_mutex_lock_iothread ( ) ;
 ret = kvm_handle_halt ( cpu ) ;
 qemu_mutex_unlock_iothread ( ) ;
 break ;
 case KVM_EXIT_SET_TPR : ret = 0 ;
 break ;
 case KVM_EXIT_TPR_ACCESS : qemu_mutex_lock_iothread ( ) ;
 ret = kvm_handle_tpr_access ( cpu ) ;
 qemu_mutex_unlock_iothread ( ) ;
 break ;
 case KVM_EXIT_FAIL_ENTRY : code = run -> fail_entry . hardware_entry_failure_reason ;
 fprintf ( stderr , "KVM: entry failed, hardware error 0x%" PRIx64 "\n" , code ) ;
 if ( host_supports_vmx ( ) && code == VMX_INVALID_GUEST_STATE ) {
 fprintf ( stderr , "\nIf you're running a guest on an Intel machine without " "unrestricted mode\n" "support, the failure can be most likely due to the guest " "entering an invalid\n" "state for Intel VT. For example, the guest maybe running " "in big real mode\n" "which is not supported on less recent Intel processors." "\n\n" ) ;
 }
 ret = - 1 ;
 break ;
 case KVM_EXIT_EXCEPTION : fprintf ( stderr , "KVM: exception %d exit (error code 0x%x)\n" , run -> ex . exception , run -> ex . error_code ) ;
 ret = - 1 ;
 break ;
 case KVM_EXIT_DEBUG : DPRINTF ( "kvm_exit_debug\n" ) ;
 qemu_mutex_lock_iothread ( ) ;
 ret = kvm_handle_debug ( cpu , & run -> debug . arch ) ;
 qemu_mutex_unlock_iothread ( ) ;
 break ;
 case KVM_EXIT_HYPERV : ret = kvm_hv_handle_exit ( cpu , & run -> hyperv ) ;
 break ;
 case KVM_EXIT_IOAPIC_EOI : ioapic_eoi_broadcast ( run -> eoi . vector ) ;
 ret = 0 ;
 break ;
 default : fprintf ( stderr , "KVM: unknown exit reason %d\n" , run -> exit_reason ) ;
 ret = - 1 ;
 break ;
 }
 return ret ;
 }