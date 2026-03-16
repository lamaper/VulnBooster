MemTxAttrs kvm_arch_post_run ( CPUState * cpu , struct kvm_run * run ) {
 X86CPU * x86_cpu = X86_CPU ( cpu ) ;
 CPUX86State * env = & x86_cpu -> env ;
 if ( run -> flags & KVM_RUN_X86_SMM ) {
 env -> hflags |= HF_SMM_MASK ;
 }
 else {
 env -> hflags &= ~ HF_SMM_MASK ;
 }
 if ( run -> if_flag ) {
 env -> eflags |= IF_MASK ;
 }
 else {
 env -> eflags &= ~ IF_MASK ;
 }
 if ( ! kvm_irqchip_in_kernel ( ) ) {
 qemu_mutex_lock_iothread ( ) ;
 }
 cpu_set_apic_tpr ( x86_cpu -> apic_state , run -> cr8 ) ;
 cpu_set_apic_base ( x86_cpu -> apic_state , run -> apic_base ) ;
 if ( ! kvm_irqchip_in_kernel ( ) ) {
 qemu_mutex_unlock_iothread ( ) ;
 }
 return cpu_get_mem_attrs ( env ) ;
 }