static void kvm_msr_entry_add ( X86CPU * cpu , uint32_t index , uint64_t value ) {
 struct kvm_msrs * msrs = cpu -> kvm_msr_buf ;
 void * limit = ( ( void * ) msrs ) + MSR_BUF_SIZE ;
 struct kvm_msr_entry * entry = & msrs -> entries [ msrs -> nmsrs ] ;
 assert ( ( void * ) ( entry + 1 ) <= limit ) ;
 entry -> index = index ;
 entry -> reserved = 0 ;
 entry -> data = value ;
 msrs -> nmsrs ++ ;
 }