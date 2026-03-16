static inline void write_IRQreg_ivpr ( OpenPICState * opp , int n_IRQ , uint32_t val ) {
 uint32_t mask ;
 mask = IVPR_MASK_MASK | IVPR_PRIORITY_MASK | IVPR_SENSE_MASK | IVPR_POLARITY_MASK | opp -> vector_mask ;
 opp -> src [ n_IRQ ] . ivpr = ( opp -> src [ n_IRQ ] . ivpr & IVPR_ACTIVITY_MASK ) | ( val & mask ) ;
 switch ( opp -> src [ n_IRQ ] . type ) {
 case IRQ_TYPE_NORMAL : opp -> src [ n_IRQ ] . level = ! ! ( opp -> src [ n_IRQ ] . ivpr & IVPR_SENSE_MASK ) ;
 break ;
 case IRQ_TYPE_FSLINT : opp -> src [ n_IRQ ] . ivpr &= ~ IVPR_SENSE_MASK ;
 break ;
 case IRQ_TYPE_FSLSPECIAL : opp -> src [ n_IRQ ] . ivpr &= ~ ( IVPR_POLARITY_MASK | IVPR_SENSE_MASK ) ;
 break ;
 }
 openpic_update_irq ( opp , n_IRQ ) ;
 DPRINTF ( "Set IVPR %d to 0x%08x -> 0x%08x\n" , n_IRQ , val , opp -> src [ n_IRQ ] . ivpr ) ;
 }