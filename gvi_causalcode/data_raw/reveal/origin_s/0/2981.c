void kvm_put_apicbase ( X86CPU * cpu , uint64_t value ) {
 int ret ;
 ret = kvm_put_one_msr ( cpu , MSR_IA32_APICBASE , value ) ;
 assert ( ret == 1 ) ;
 }