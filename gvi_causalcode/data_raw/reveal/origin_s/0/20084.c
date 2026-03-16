static void gic_set_running_irq ( GICState * s , int cpu , int irq ) {
 s -> running_irq [ cpu ] = irq ;
 if ( irq == 1023 ) {
 s -> running_priority [ cpu ] = 0x100 ;
 }
 else {
 s -> running_priority [ cpu ] = GIC_GET_PRIORITY ( irq , cpu ) ;
 }
 gic_update ( s ) ;
 }