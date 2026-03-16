static void kvm_msr_buf_reset ( X86CPU * cpu ) {
 memset ( cpu -> kvm_msr_buf , 0 , MSR_BUF_SIZE ) ;
 }