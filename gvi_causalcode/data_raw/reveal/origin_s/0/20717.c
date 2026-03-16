static bool hyperv_hypercall_available ( X86CPU * cpu ) {
 return cpu -> hyperv_vapic || ( cpu -> hyperv_spinlock_attempts != HYPERV_SPINLOCK_NEVER_RETRY ) ;
 }