static void vapic_enable_tpr_reporting ( bool enable ) {
 VAPICEnableTPRReporting info = {
 . enable = enable , }
 ;
 X86CPU * cpu ;
 CPUX86State * env ;
 for ( env = first_cpu ;
 env != NULL ;
 env = env -> next_cpu ) {
 cpu = x86_env_get_cpu ( env ) ;
 info . apic = env -> apic_state ;
 run_on_cpu ( CPU ( cpu ) , vapic_do_enable_tpr_reporting , & info ) ;
 }
 }