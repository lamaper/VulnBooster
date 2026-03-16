static void pcnet_update_irq ( PCNetState * s ) {
 int isr = 0 ;
 s -> csr [ 0 ] &= ~ 0x0080 ;

 isr = CSR_INEA ( s ) ;
 s -> csr [ 0 ] |= 0x0080 ;
 }
 if ( ! ! ( s -> csr [ 4 ] & 0x0080 ) && CSR_INEA ( s ) ) {
 s -> csr [ 4 ] &= ~ 0x0080 ;
 s -> csr [ 4 ] |= 0x0040 ;
 s -> csr [ 0 ] |= 0x0080 ;
 isr = 1 ;
 trace_pcnet_user_int ( s ) ;
 }

 isr = 1 ;
 s -> csr [ 0 ] |= 0x0080 ;
 }
 if ( isr != s -> isr ) {
 trace_pcnet_isr_change ( s , isr , s -> isr ) ;
 }
 qemu_set_irq ( s -> irq , isr ) ;
 s -> isr = isr ;
 }