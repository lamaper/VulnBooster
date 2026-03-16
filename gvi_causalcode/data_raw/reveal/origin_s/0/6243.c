int qemuMonitorTextAttachPCIDiskController ( qemuMonitorPtr mon , const char * bus , virDomainDevicePCIAddress * guestAddr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 int tryOldSyntax = 0 ;
 int ret = - 1 ;
 try_command : if ( virAsprintf ( & cmd , "pci_add %s storage if=%s" , ( tryOldSyntax ? "0" : "pci_addr=auto" ) , bus ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "cannot attach %s disk controller" ) , bus ) ;
 goto cleanup ;
 }
 if ( qemuMonitorTextParsePciAddReply ( mon , reply , guestAddr ) < 0 ) {
 if ( ! tryOldSyntax && strstr ( reply , "invalid char in expression" ) ) {
 VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 tryOldSyntax = 1 ;
 goto try_command ;
 }
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "adding %s disk controller failed: %s" ) , bus , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }