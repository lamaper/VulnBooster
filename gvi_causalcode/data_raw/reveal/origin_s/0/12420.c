static void xhci_port_notify ( XHCIPort * port , uint32_t bits ) {
 XHCIEvent ev = {
 ER_PORT_STATUS_CHANGE , CC_SUCCESS , port -> portnr << 24 }
 ;
 if ( ( port -> portsc & bits ) == bits ) {
 return ;
 }
 trace_usb_xhci_port_notify ( port -> portnr , bits ) ;
 port -> portsc |= bits ;
 if ( ! xhci_running ( port -> xhci ) ) {
 return ;
 }
 xhci_event ( port -> xhci , & ev , 0 ) ;
 }