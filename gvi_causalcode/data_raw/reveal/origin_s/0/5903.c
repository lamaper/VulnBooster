void kvm_arch_pre_run ( CPUState * cpu , struct kvm_run * run ) {
 X86CPU * x86_cpu = X86_CPU ( cpu ) ;
 CPUX86State * env = & x86_cpu -> env ;
 int ret ;
 if ( cpu -> interrupt_request & ( CPU_INTERRUPT_NMI | CPU_INTERRUPT_SMI ) ) {
 if ( cpu -> interrupt_request & CPU_INTERRUPT_NMI ) {
 qemu_mutex_lock_iothread ( ) ;
 cpu -> interrupt_request &= ~ CPU_INTERRUPT_NMI ;
 qemu_mutex_unlock_iothread ( ) ;
 DPRINTF ( "injected NMI\n" ) ;
 ret = kvm_vcpu_ioctl ( cpu , KVM_NMI ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "KVM: injection failed, NMI lost (%s)\n" , strerror ( - ret ) ) ;
 }
 }
 if ( cpu -> interrupt_request & CPU_INTERRUPT_SMI ) {
 qemu_mutex_lock_iothread ( ) ;
 cpu -> interrupt_request &= ~ CPU_INTERRUPT_SMI ;
 qemu_mutex_unlock_iothread ( ) ;
 DPRINTF ( "injected SMI\n" ) ;
 ret = kvm_vcpu_ioctl ( cpu , KVM_SMI ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "KVM: injection failed, SMI lost (%s)\n" , strerror ( - ret ) ) ;
 }
 }
 }
 if ( ! kvm_pic_in_kernel ( ) ) {
 qemu_mutex_lock_iothread ( ) ;
 }
 if ( cpu -> interrupt_request & ( CPU_INTERRUPT_INIT | CPU_INTERRUPT_TPR ) ) {
 if ( ( cpu -> interrupt_request & CPU_INTERRUPT_INIT ) && ! ( env -> hflags & HF_SMM_MASK ) ) {
 cpu -> exit_request = 1 ;
 }
 if ( cpu -> interrupt_request & CPU_INTERRUPT_TPR ) {
 cpu -> exit_request = 1 ;
 }
 }
 if ( ! kvm_pic_in_kernel ( ) ) {
 if ( run -> ready_for_interrupt_injection && ( cpu -> interrupt_request & CPU_INTERRUPT_HARD ) && ( env -> eflags & IF_MASK ) ) {
 int irq ;
 cpu -> interrupt_request &= ~ CPU_INTERRUPT_HARD ;
 irq = cpu_get_pic_interrupt ( env ) ;
 if ( irq >= 0 ) {
 struct kvm_interrupt intr ;
 intr . irq = irq ;
 DPRINTF ( "injected interrupt %d\n" , irq ) ;
 ret = kvm_vcpu_ioctl ( cpu , KVM_INTERRUPT , & intr ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "KVM: injection failed, interrupt lost (%s)\n" , strerror ( - ret ) ) ;
 }
 }
 }
 if ( ( cpu -> interrupt_request & CPU_INTERRUPT_HARD ) ) {
 run -> request_interrupt_window = 1 ;
 }
 else {
 run -> request_interrupt_window = 0 ;
 }
 DPRINTF ( "setting tpr\n" ) ;
 run -> cr8 = cpu_get_apic_tpr ( x86_cpu -> apic_state ) ;
 qemu_mutex_unlock_iothread ( ) ;
 }
 }