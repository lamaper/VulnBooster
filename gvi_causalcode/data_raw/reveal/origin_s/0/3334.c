void pause_all_vcpus ( void ) {
 CPUArchState * penv = first_cpu ;
 qemu_clock_enable ( vm_clock , false ) ;
 while ( penv ) {
 CPUState * pcpu = ENV_GET_CPU ( penv ) ;
 pcpu -> stop = true ;
 qemu_cpu_kick ( pcpu ) ;
 penv = penv -> next_cpu ;
 }
 if ( qemu_in_vcpu_thread ( ) ) {
 cpu_stop_current ( ) ;
 if ( ! kvm_enabled ( ) ) {
 penv = first_cpu ;
 while ( penv ) {
 CPUState * pcpu = ENV_GET_CPU ( penv ) ;
 pcpu -> stop = false ;
 pcpu -> stopped = true ;
 penv = penv -> next_cpu ;
 }
 return ;
 }
 }
 while ( ! all_vcpus_paused ( ) ) {
 qemu_cond_wait ( & qemu_pause_cond , & qemu_global_mutex ) ;
 penv = first_cpu ;
 while ( penv ) {
 qemu_cpu_kick ( ENV_GET_CPU ( penv ) ) ;
 penv = penv -> next_cpu ;
 }
 }
 }