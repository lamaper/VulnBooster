static uint64_t openpic_src_read ( void * opaque , uint64_t addr , unsigned len ) {
 OpenPICState * opp = opaque ;
 uint32_t retval ;
 int idx ;
 DPRINTF ( "%s: addr %#" HWADDR_PRIx "\n" , __func__ , addr ) ;
 retval = 0xFFFFFFFF ;
 addr = addr & 0xffff ;
 idx = addr >> 5 ;
 switch ( addr & 0x1f ) {
 case 0x00 : retval = read_IRQreg_ivpr ( opp , idx ) ;
 break ;
 case 0x10 : retval = read_IRQreg_idr ( opp , idx ) ;
 break ;
 case 0x18 : retval = read_IRQreg_ilr ( opp , idx ) ;
 break ;
 }
 DPRINTF ( "%s: => 0x%08x\n" , __func__ , retval ) ;
 return retval ;
 }