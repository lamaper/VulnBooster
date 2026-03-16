static void openpic_reset ( DeviceState * d ) {
 OpenPICState * opp = OPENPIC ( d ) ;
 int i ;
 opp -> gcr = GCR_RESET ;
 opp -> frr = ( ( opp -> nb_irqs - 1 ) << FRR_NIRQ_SHIFT ) | ( ( opp -> nb_cpus - 1 ) << FRR_NCPU_SHIFT ) | ( opp -> vid << FRR_VID_SHIFT ) ;
 opp -> pir = 0 ;
 opp -> spve = - 1 & opp -> vector_mask ;
 opp -> tfrr = opp -> tfrr_reset ;
 for ( i = 0 ;
 i < opp -> max_irq ;
 i ++ ) {
 opp -> src [ i ] . ivpr = opp -> ivpr_reset ;
 opp -> src [ i ] . idr = opp -> idr_reset ;
 switch ( opp -> src [ i ] . type ) {
 case IRQ_TYPE_NORMAL : opp -> src [ i ] . level = ! ! ( opp -> ivpr_reset & IVPR_SENSE_MASK ) ;
 break ;
 case IRQ_TYPE_FSLINT : opp -> src [ i ] . ivpr |= IVPR_POLARITY_MASK ;
 break ;
 case IRQ_TYPE_FSLSPECIAL : break ;
 }
 }
 for ( i = 0 ;
 i < MAX_CPU ;
 i ++ ) {
 opp -> dst [ i ] . ctpr = 15 ;
 memset ( & opp -> dst [ i ] . raised , 0 , sizeof ( IRQQueue ) ) ;
 opp -> dst [ i ] . raised . next = - 1 ;
 memset ( & opp -> dst [ i ] . servicing , 0 , sizeof ( IRQQueue ) ) ;
 opp -> dst [ i ] . servicing . next = - 1 ;
 }
 for ( i = 0 ;
 i < OPENPIC_MAX_TMR ;
 i ++ ) {
 opp -> timers [ i ] . tccr = 0 ;
 opp -> timers [ i ] . tbcr = TBCR_CI ;
 }
 opp -> gcr = 0 ;
 }