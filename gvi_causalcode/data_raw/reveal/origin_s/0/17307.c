void pcnet_ioport_writel ( void * opaque , uint32_t addr , uint32_t val ) {
 PCNetState * s = opaque ;
 pcnet_poll_timer ( s ) ;


 switch ( addr & 0x0f ) {
 case 0x00 : pcnet_csr_writew ( s , s -> rap , val & 0xffff ) ;
 break ;
 case 0x04 : s -> rap = val & 0x7f ;
 break ;
 case 0x0c : pcnet_bcr_writew ( s , s -> rap , val & 0xffff ) ;
 break ;
 }
 }
 else if ( ( addr & 0x0f ) == 0 ) {
 pcnet_bcr_writew ( s , BCR_BSBC , pcnet_bcr_readw ( s , BCR_BSBC ) | 0x0080 ) ;


 pcnet_update_irq ( s ) ;
 }