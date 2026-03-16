static int kvm_handle_tpr_access ( X86CPU * cpu ) {
 CPUState * cs = CPU ( cpu ) ;
 struct kvm_run * run = cs -> kvm_run ;
 apic_handle_tpr_access_report ( cpu -> apic_state , run -> tpr_access . rip , run -> tpr_access . is_write ? TPR_ACCESS_WRITE : TPR_ACCESS_READ ) ;
 return 1 ;
 }