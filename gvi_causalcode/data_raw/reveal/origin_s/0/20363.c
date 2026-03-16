uint32_t gic_acknowledge_irq ( GICState * s , int cpu ) {
 int new_irq ;
 int cm = 1 << cpu ;
 new_irq = s -> current_pending [ cpu ] ;
 if ( new_irq == 1023 || GIC_GET_PRIORITY ( new_irq , cpu ) >= s -> running_priority [ cpu ] ) {
 DPRINTF ( "ACK no pending IRQ\n" ) ;
 return 1023 ;
 }
 s -> last_active [ new_irq ] [ cpu ] = s -> running_irq [ cpu ] ;
 GIC_CLEAR_PENDING ( new_irq , GIC_TEST_MODEL ( new_irq ) ? ALL_CPU_MASK : cm ) ;
 gic_set_running_irq ( s , cpu , new_irq ) ;
 DPRINTF ( "ACK %d\n" , new_irq ) ;
 return new_irq ;
 }