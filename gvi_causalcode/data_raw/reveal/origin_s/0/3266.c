static int qemuAgentCheckError ( virJSONValuePtr cmd , virJSONValuePtr reply ) {
 if ( virJSONValueObjectHasKey ( reply , "error" ) ) {
 virJSONValuePtr error = virJSONValueObjectGet ( reply , "error" ) ;
 char * cmdstr = virJSONValueToString ( cmd , false ) ;
 char * replystr = virJSONValueToString ( reply , false ) ;
 VIR_DEBUG ( "unable to execute QEMU agent command %s: %s" , NULLSTR ( cmdstr ) , NULLSTR ( replystr ) ) ;
 if ( ! error ) virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU agent command '%s'" ) , qemuAgentCommandName ( cmd ) ) ;
 else virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU agent command '%s': %s" ) , qemuAgentCommandName ( cmd ) , qemuAgentStringifyError ( error ) ) ;
 VIR_FREE ( cmdstr ) ;
 VIR_FREE ( replystr ) ;
 return - 1 ;
 }
 else if ( ! virJSONValueObjectHasKey ( reply , "return" ) ) {
 char * cmdstr = virJSONValueToString ( cmd , false ) ;
 char * replystr = virJSONValueToString ( reply , false ) ;
 VIR_DEBUG ( "Neither 'return' nor 'error' is set in the JSON reply %s: %s" , NULLSTR ( cmdstr ) , NULLSTR ( replystr ) ) ;
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to execute QEMU agent command '%s'" ) , qemuAgentCommandName ( cmd ) ) ;
 VIR_FREE ( cmdstr ) ;
 VIR_FREE ( replystr ) ;
 return - 1 ;
 }
 return 0 ;
 }