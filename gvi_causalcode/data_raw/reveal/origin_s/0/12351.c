static void openpic_src_write ( void * opaque , hwaddr addr , uint64_t val , unsigned len ) {
 OpenPICState * opp = opaque ;
 int idx ;
 DPRINTF ( "%s: addr %#" HWADDR_PRIx " <= %08" PRIx64 "\n" , __func__ , addr , val ) ;
 addr = addr & 0xffff ;
 idx = addr >> 5 ;
 switch ( addr & 0x1f ) {
 case 0x00 : write_IRQreg_ivpr ( opp , idx , val ) ;
 break ;
 case 0x10 : write_IRQreg_idr ( opp , idx , val ) ;
 break ;
 case 0x18 : write_IRQreg_ilr ( opp , idx , val ) ;
 break ;
 }
 }