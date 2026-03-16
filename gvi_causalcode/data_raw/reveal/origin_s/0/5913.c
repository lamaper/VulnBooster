static void gic_set_irq ( void * opaque , int irq , int level ) {
 GICState * s = ( GICState * ) opaque ;
 int cm , target ;
 if ( irq < ( s -> num_irq - GIC_INTERNAL ) ) {
 cm = ALL_CPU_MASK ;
 irq += GIC_INTERNAL ;
 target = GIC_TARGET ( irq ) ;
 }
 else {
 int cpu ;
 irq -= ( s -> num_irq - GIC_INTERNAL ) ;
 cpu = irq / GIC_INTERNAL ;
 irq %= GIC_INTERNAL ;
 cm = 1 << cpu ;
 target = cm ;
 }
 if ( level == GIC_TEST_LEVEL ( irq , cm ) ) {
 return ;
 }
 if ( level ) {
 GIC_SET_LEVEL ( irq , cm ) ;
 if ( GIC_TEST_TRIGGER ( irq ) || GIC_TEST_ENABLED ( irq , cm ) ) {
 DPRINTF ( "Set %d pending mask %x\n" , irq , target ) ;
 GIC_SET_PENDING ( irq , target ) ;
 }
 }
 else {
 GIC_CLEAR_LEVEL ( irq , cm ) ;
 }
 gic_update ( s ) ;
 }