static uint64_t xhci_runtime_read ( void * ptr , hwaddr reg , unsigned size ) {
 XHCIState * xhci = ptr ;
 uint32_t ret = 0 ;
 if ( reg < 0x20 ) {
 switch ( reg ) {
 case 0x00 : ret = xhci_mfindex_get ( xhci ) & 0x3fff ;
 break ;
 default : trace_usb_xhci_unimplemented ( "runtime read" , reg ) ;
 break ;
 }
 }
 else {
 int v = ( reg - 0x20 ) / 0x20 ;
 XHCIInterrupter * intr = & xhci -> intr [ v ] ;
 switch ( reg & 0x1f ) {
 case 0x00 : ret = intr -> iman ;
 break ;
 case 0x04 : ret = intr -> imod ;
 break ;
 case 0x08 : ret = intr -> erstsz ;
 break ;
 case 0x10 : ret = intr -> erstba_low ;
 break ;
 case 0x14 : ret = intr -> erstba_high ;
 break ;
 case 0x18 : ret = intr -> erdp_low ;
 break ;
 case 0x1c : ret = intr -> erdp_high ;
 break ;
 }
 }
 trace_usb_xhci_runtime_read ( reg , ret ) ;
 return ret ;
 }