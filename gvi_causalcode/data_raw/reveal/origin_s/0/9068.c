static void openpic_save ( QEMUFile * f , void * opaque ) {
 OpenPICState * opp = ( OpenPICState * ) opaque ;
 unsigned int i ;
 qemu_put_be32s ( f , & opp -> gcr ) ;
 qemu_put_be32s ( f , & opp -> vir ) ;
 qemu_put_be32s ( f , & opp -> pir ) ;
 qemu_put_be32s ( f , & opp -> spve ) ;
 qemu_put_be32s ( f , & opp -> tfrr ) ;
 qemu_put_be32s ( f , & opp -> nb_cpus ) ;
 for ( i = 0 ;
 i < opp -> nb_cpus ;
 i ++ ) {
 qemu_put_sbe32s ( f , & opp -> dst [ i ] . ctpr ) ;
 openpic_save_IRQ_queue ( f , & opp -> dst [ i ] . raised ) ;
 openpic_save_IRQ_queue ( f , & opp -> dst [ i ] . servicing ) ;
 qemu_put_buffer ( f , ( uint8_t * ) & opp -> dst [ i ] . outputs_active , sizeof ( opp -> dst [ i ] . outputs_active ) ) ;
 }
 for ( i = 0 ;
 i < OPENPIC_MAX_TMR ;
 i ++ ) {
 qemu_put_be32s ( f , & opp -> timers [ i ] . tccr ) ;
 qemu_put_be32s ( f , & opp -> timers [ i ] . tbcr ) ;
 }
 for ( i = 0 ;
 i < opp -> max_irq ;
 i ++ ) {
 qemu_put_be32s ( f , & opp -> src [ i ] . ivpr ) ;
 qemu_put_be32s ( f , & opp -> src [ i ] . idr ) ;
 qemu_get_be32s ( f , & opp -> src [ i ] . destmask ) ;
 qemu_put_sbe32s ( f , & opp -> src [ i ] . last_cpu ) ;
 qemu_put_sbe32s ( f , & opp -> src [ i ] . pending ) ;
 }
 }