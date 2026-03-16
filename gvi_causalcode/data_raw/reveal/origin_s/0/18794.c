void kvm_synchronize_all_tsc ( void ) {
 CPUState * cpu ;
 if ( kvm_enabled ( ) ) {
 CPU_FOREACH ( cpu ) {
 run_on_cpu ( cpu , do_kvm_synchronize_tsc , RUN_ON_CPU_NULL ) ;
 }
 }
 }