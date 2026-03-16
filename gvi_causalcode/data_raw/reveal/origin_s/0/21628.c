static int vapic_post_load ( void * opaque , int version_id ) {
 VAPICROMState * s = opaque ;
 uint8_t * zero ;
 if ( s -> state == VAPIC_INACTIVE && s -> rom_state_paddr != 0 ) {
 s -> state = VAPIC_STANDBY ;
 }
 if ( s -> state != VAPIC_INACTIVE ) {
 if ( vapic_prepare ( s ) < 0 ) {
 return - 1 ;
 }
 }
 if ( s -> state == VAPIC_ACTIVE ) {
 if ( smp_cpus == 1 ) {
 run_on_cpu ( ENV_GET_CPU ( first_cpu ) , do_vapic_enable , s ) ;
 }
 else {
 zero = g_malloc0 ( s -> rom_state . vapic_size ) ;
 cpu_physical_memory_rw ( s -> vapic_paddr , zero , s -> rom_state . vapic_size , 1 ) ;
 g_free ( zero ) ;
 }
 }
 return 0 ;
 }