static void openpic_set_irq ( void * opaque , int n_IRQ , int level ) {
 OpenPICState * opp = opaque ;
 IRQSource * src ;
 if ( n_IRQ >= OPENPIC_MAX_IRQ ) {
 fprintf ( stderr , "%s: IRQ %d out of range\n" , __func__ , n_IRQ ) ;
 abort ( ) ;
 }
 src = & opp -> src [ n_IRQ ] ;
 DPRINTF ( "openpic: set irq %d = %d ivpr=0x%08x\n" , n_IRQ , level , src -> ivpr ) ;
 if ( src -> level ) {
 src -> pending = level ;
 openpic_update_irq ( opp , n_IRQ ) ;
 }
 else {
 if ( level ) {
 src -> pending = 1 ;
 openpic_update_irq ( opp , n_IRQ ) ;
 }
 if ( src -> output != OPENPIC_OUTPUT_INT ) {
 src -> pending = 0 ;
 openpic_update_irq ( opp , n_IRQ ) ;
 }
 }
 }