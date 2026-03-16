static inline void write_IRQreg_ilr ( OpenPICState * opp , int n_IRQ , uint32_t val ) {
 if ( opp -> flags & OPENPIC_FLAG_ILR ) {
 IRQSource * src = & opp -> src [ n_IRQ ] ;
 src -> output = inttgt_to_output ( val & ILR_INTTGT_MASK ) ;
 DPRINTF ( "Set ILR %d to 0x%08x, output %d\n" , n_IRQ , src -> idr , src -> output ) ;
 }
 }