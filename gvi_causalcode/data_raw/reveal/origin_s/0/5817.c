int qemuMonitorTextAddPCIDisk ( qemuMonitorPtr mon , const char * path , const char * bus , virDomainDevicePCIAddress * guestAddr ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safe_path = NULL ;
 int tryOldSyntax = 0 ;
 int ret = - 1 ;
 safe_path = qemuMonitorEscapeArg ( path ) ;
 if ( ! safe_path ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 try_command : if ( virAsprintf ( & cmd , "pci_add %s storage file=%s,if=%s" , ( tryOldSyntax ? "0" : "pci_addr=auto" ) , safe_path , bus ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "cannot attach %s disk %s" ) , bus , path ) ;
 goto cleanup ;
 }
 if ( qemuMonitorTextParsePciAddReply ( mon , reply , guestAddr ) < 0 ) {
 if ( ! tryOldSyntax && strstr ( reply , "invalid char in expression" ) ) {
 VIR_FREE ( reply ) ;
 VIR_FREE ( cmd ) ;
 tryOldSyntax = 1 ;
 goto try_command ;
 }
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "adding %s disk failed %s: %s" ) , bus , path , reply ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( safe_path ) ;
 VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }