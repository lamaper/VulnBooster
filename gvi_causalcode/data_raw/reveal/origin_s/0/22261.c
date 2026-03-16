static inline void do_kvm_synchronize_tsc ( CPUState * cpu , run_on_cpu_data arg ) {
 kvm_get_tsc ( cpu ) ;
 }