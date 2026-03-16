static bool kvm_x2apic_api_set_flags ( uint64_t flags ) {
 KVMState * s = KVM_STATE ( current_machine -> accelerator ) ;
 return ! kvm_vm_enable_cap ( s , KVM_CAP_X2APIC_API , 0 , flags ) ;
 }