int qemuMonitorTextRemovePCIDevice ( qemuMonitorPtr mon , virDomainDevicePCIAddress * guestAddr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int tryOldSyntax = 0 ;
 int ret = - 1 ;
 try_command : if ( tryOldSyntax ) {
 if ( virAsprintf ( & cmd , "pci_del 0 %.2x" , guestAddr -> slot ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 }
 else {
 if ( virAsprintf ( & cmd , "pci_del pci_addr=%.4x:%.2x:%.2x" , guestAddr -> domain , guestAddr -> bus , guestAddr -> slot ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "failed to remove PCI device" ) ) ;
 goto cleanup ;
 }
 if ( ! tryOldSyntax && strstr ( reply , "extraneous characters" ) ) {
 tryOldSyntax = 1 ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 goto try_command ;
 }
 if ( strstr ( reply , "invalid slot" ) || strstr ( reply , "Invalid pci address" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to detach PCI device, invalid address %.4x:%.2x:%.2x: %s" ) , guestAddr -> domain , guestAddr -> bus , guestAddr -> slot , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }