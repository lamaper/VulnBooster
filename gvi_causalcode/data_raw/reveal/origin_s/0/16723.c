int qemuMonitorTextAddPCIHostDevice ( qemuMonitorPtr mon , virDomainDevicePCIAddress * hostAddr , virDomainDevicePCIAddress * guestAddr ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 memset ( guestAddr , 0 , sizeof ( * guestAddr ) ) ;
 if ( virAsprintf ( & cmd , "pci_add pci_addr=auto host host=%.2x:%.2x.%.1x" , hostAddr -> bus , hostAddr -> slot , hostAddr -> function ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot attach host pci device" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "invalid type: host" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "PCI device assignment is not supported by this version of qemu" ) ) ;
 goto cleanup ;
 }
 if ( qemuMonitorTextParsePciAddReply ( mon , reply , guestAddr ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "parsing pci_add reply failed: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }