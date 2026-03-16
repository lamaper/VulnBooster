void qemu_init_vcpu ( CPUState * cpu ) {
 cpu -> nr_cores = smp_cores ;
 cpu -> nr_threads = smp_threads ;
 cpu -> stopped = true ;
 if ( kvm_enabled ( ) ) {
 qemu_kvm_start_vcpu ( cpu ) ;
 }
 else if ( tcg_enabled ( ) ) {
 qemu_tcg_init_vcpu ( cpu ) ;
 }
 else {
 qemu_dummy_start_vcpu ( cpu ) ;
 }
 }