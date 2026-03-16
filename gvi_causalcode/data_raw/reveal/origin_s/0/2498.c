static inline void write_IRQreg_idr ( OpenPICState * opp , int n_IRQ , uint32_t val ) {
 IRQSource * src = & opp -> src [ n_IRQ ] ;
 uint32_t normal_mask = ( 1UL << opp -> nb_cpus ) - 1 ;
 uint32_t crit_mask = 0 ;
 uint32_t mask = normal_mask ;
 int crit_shift = IDR_EP_SHIFT - opp -> nb_cpus ;
 int i ;
 if ( opp -> flags & OPENPIC_FLAG_IDR_CRIT ) {
 crit_mask = mask << crit_shift ;
 mask |= crit_mask | IDR_EP ;
 }
 src -> idr = val & mask ;
 DPRINTF ( "Set IDR %d to 0x%08x\n" , n_IRQ , src -> idr ) ;
 if ( opp -> flags & OPENPIC_FLAG_IDR_CRIT ) {
 if ( src -> idr & crit_mask ) {
 if ( src -> idr & normal_mask ) {
 DPRINTF ( "%s: IRQ configured for multiple output types, using " "critical\n" , __func__ ) ;
 }
 src -> output = OPENPIC_OUTPUT_CINT ;
 src -> nomask = true ;
 src -> destmask = 0 ;
 for ( i = 0 ;
 i < opp -> nb_cpus ;
 i ++ ) {
 int n_ci = IDR_CI0_SHIFT - i ;
 if ( src -> idr & ( 1UL << n_ci ) ) {
 src -> destmask |= 1UL << i ;
 }
 }
 }
 else {
 src -> output = OPENPIC_OUTPUT_INT ;
 src -> nomask = false ;
 src -> destmask = src -> idr & normal_mask ;
 }
 }
 else {
 src -> destmask = src -> idr ;
 }
 }