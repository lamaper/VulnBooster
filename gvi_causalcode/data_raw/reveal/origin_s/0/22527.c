bool kvm_enable_x2apic ( void ) {
 return MEMORIZE ( kvm_x2apic_api_set_flags ( KVM_X2APIC_API_USE_32BIT_IDS | KVM_X2APIC_API_DISABLE_BROADCAST_QUIRK ) , has_x2apic_api ) ;
 }