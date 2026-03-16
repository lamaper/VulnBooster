int qemuMonitorTextAddPCINetwork ( qemuMonitorPtr mon , const char * nicstr , virDomainDevicePCIAddress * guestAddr ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "pci_add pci_addr=auto nic %s" , nicstr ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to add NIC with '%s'" ) , cmd ) ;
 goto cleanup ;
 }
 if ( qemuMonitorTextParsePciAddReply ( mon , reply , guestAddr ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "parsing pci_add reply failed: %s" ) , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }