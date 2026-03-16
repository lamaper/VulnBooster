static int qemuMonitorJSONCheckError ( virJSONValuePtr cmd , virJSONValuePtr reply ) {
 if ( virJSONValueObjectHasKey ( reply , "error" ) ) {
 virJSONValuePtr error = virJSONValueObjectGet ( reply , "error" ) ;
 char * cmdstr = virJSONValueToString ( cmd ) ;
 char * replystr = virJSONValueToString ( reply ) ;
 VIR_DEBUG ( "unable to execute QEMU command %s: %s" , cmdstr , replystr ) ;
 if ( ! error ) qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU command '%s'" ) , qemuMonitorJSONCommandName ( cmd ) ) ;
 else qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU command '%s': %s" ) , qemuMonitorJSONCommandName ( cmd ) , qemuMonitorJSONStringifyError ( error ) ) ;
 VIR_FREE ( cmdstr ) ;
 VIR_FREE ( replystr ) ;
 return - 1 ;
 }
 else if ( ! virJSONValueObjectHasKey ( reply , "return" ) ) {
 char * cmdstr = virJSONValueToString ( cmd ) ;
 char * replystr = virJSONValueToString ( reply ) ;
 VIR_DEBUG ( "Neither 'return' nor 'error' is set in the JSON reply %s: %s" , cmdstr , replystr ) ;
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU command '%s'" ) , qemuMonitorJSONCommandName ( cmd ) ) ;
 VIR_FREE ( cmdstr ) ;
 VIR_FREE ( replystr ) ;
 return - 1 ;
 }
 return 0 ;
 }