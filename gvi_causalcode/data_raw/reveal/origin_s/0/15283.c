static void PREP_io_800_writeb ( void * opaque , uint32_t addr , uint32_t val ) {
 sysctrl_t * sysctrl = opaque ;
 PPC_IO_DPRINTF ( "0x%08" PRIx32 " => 0x%02" PRIx32 "\n" , addr - PPC_IO_BASE , val ) ;
 switch ( addr ) {
 case 0x0092 : if ( val & 0x01 ) {
 qemu_irq_raise ( sysctrl -> reset_irq ) ;
 }
 else {
 qemu_irq_lower ( sysctrl -> reset_irq ) ;
 }
 if ( val & 0x02 ) {
 sysctrl -> endian = 1 ;
 }
 else {
 sysctrl -> endian = 0 ;
 }
 break ;
 case 0x0800 : break ;
 case 0x0802 : break ;
 case 0x0803 : break ;
 case 0x0808 : if ( val & 1 ) sysctrl -> state |= STATE_HARDFILE ;
 else sysctrl -> state &= ~ STATE_HARDFILE ;
 break ;
 case 0x0810 : if ( sysctrl -> nvram != NULL ) m48t59_toggle_lock ( sysctrl -> nvram , 1 ) ;
 break ;
 case 0x0812 : if ( sysctrl -> nvram != NULL ) m48t59_toggle_lock ( sysctrl -> nvram , 2 ) ;
 break ;
 case 0x0814 : break ;
 case 0x081C : sysctrl -> syscontrol = val & 0x0F ;
 break ;
 case 0x0850 : sysctrl -> contiguous_map = val & 0x01 ;
 break ;
 default : printf ( "ERROR: unaffected IO port write: %04" PRIx32 " => %02" PRIx32 "\n" , addr , val ) ;
 break ;
 }
 }