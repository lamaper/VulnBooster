static inline uint32_t read_IRQreg_ilr ( OpenPICState * opp , int n_IRQ ) {
 if ( opp -> flags & OPENPIC_FLAG_ILR ) {
 return output_to_inttgt ( opp -> src [ n_IRQ ] . output ) ;
 }
 return 0xffffffff ;
 }