static void openpic_tmr_write ( void * opaque , hwaddr addr , uint64_t val , unsigned len ) {
 OpenPICState * opp = opaque ;
 int idx ;
 addr += 0x10f0 ;
 DPRINTF ( "%s: addr %#" HWADDR_PRIx " <= %08" PRIx64 "\n" , __func__ , addr , val ) ;
 if ( addr & 0xF ) {
 return ;
 }
 if ( addr == 0x10f0 ) {
 opp -> tfrr = val ;
 return ;
 }
 idx = ( addr >> 6 ) & 0x3 ;
 addr = addr & 0x30 ;
 switch ( addr & 0x30 ) {
 case 0x00 : break ;
 case 0x10 : if ( ( opp -> timers [ idx ] . tccr & TCCR_TOG ) != 0 && ( val & TBCR_CI ) == 0 && ( opp -> timers [ idx ] . tbcr & TBCR_CI ) != 0 ) {
 opp -> timers [ idx ] . tccr &= ~ TCCR_TOG ;
 }
 opp -> timers [ idx ] . tbcr = val ;
 break ;
 case 0x20 : write_IRQreg_ivpr ( opp , opp -> irq_tim0 + idx , val ) ;
 break ;
 case 0x30 : write_IRQreg_idr ( opp , opp -> irq_tim0 + idx , val ) ;
 break ;
 }
 }