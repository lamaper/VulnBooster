unsigned long kvm_arch_vcpu_id ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 return cpu -> apic_id ;
 }