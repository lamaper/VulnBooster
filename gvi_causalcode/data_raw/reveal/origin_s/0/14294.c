static inline uint32_t read_IRQreg_idr ( OpenPICState * opp , int n_IRQ ) {
 return opp -> src [ n_IRQ ] . idr ;
 }