static int all_vcpus_paused ( void ) {
 CPUArchState * penv = first_cpu ;
 while ( penv ) {
 CPUState * pcpu = ENV_GET_CPU ( penv ) ;
 if ( ! pcpu -> stopped ) {
 return 0 ;
 }
 penv = penv -> next_cpu ;
 }
 return 1 ;
 }