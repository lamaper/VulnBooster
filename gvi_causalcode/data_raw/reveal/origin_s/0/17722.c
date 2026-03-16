static int kvm_get_vcpu_events ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 struct kvm_vcpu_events events ;
 int ret ;
 if ( ! kvm_has_vcpu_events ( ) ) {
 return 0 ;
 }
 memset ( & events , 0 , sizeof ( events ) ) ;
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_VCPU_EVENTS , & events ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 env -> exception_injected = events . exception . injected ? events . exception . nr : - 1 ;
 env -> has_error_code = events . exception . has_error_code ;
 env -> error_code = events . exception . error_code ;
 env -> interrupt_injected = events . interrupt . injected ? events . interrupt . nr : - 1 ;
 env -> soft_interrupt = events . interrupt . soft ;
 env -> nmi_injected = events . nmi . injected ;
 env -> nmi_pending = events . nmi . pending ;
 if ( events . nmi . masked ) {
 env -> hflags2 |= HF2_NMI_MASK ;
 }
 else {
 env -> hflags2 &= ~ HF2_NMI_MASK ;
 }
 if ( events . flags & KVM_VCPUEVENT_VALID_SMM ) {
 if ( events . smi . smm ) {
 env -> hflags |= HF_SMM_MASK ;
 }
 else {
 env -> hflags &= ~ HF_SMM_MASK ;
 }
 if ( events . smi . pending ) {
 cpu_interrupt ( CPU ( cpu ) , CPU_INTERRUPT_SMI ) ;
 }
 else {
 cpu_reset_interrupt ( CPU ( cpu ) , CPU_INTERRUPT_SMI ) ;
 }
 if ( events . smi . smm_inside_nmi ) {
 env -> hflags2 |= HF2_SMM_INSIDE_NMI_MASK ;
 }
 else {
 env -> hflags2 &= ~ HF2_SMM_INSIDE_NMI_MASK ;
 }
 if ( events . smi . latched_init ) {
 cpu_interrupt ( CPU ( cpu ) , CPU_INTERRUPT_INIT ) ;
 }
 else {
 cpu_reset_interrupt ( CPU ( cpu ) , CPU_INTERRUPT_INIT ) ;
 }
 }
 env -> sipi_vector = events . sipi_vector ;
 return 0 ;
 }