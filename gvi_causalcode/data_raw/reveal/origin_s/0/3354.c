static inline uint32_t read_IRQreg_ivpr ( OpenPICState * opp , int n_IRQ ) {
 return opp -> src [ n_IRQ ] . ivpr ;
 }