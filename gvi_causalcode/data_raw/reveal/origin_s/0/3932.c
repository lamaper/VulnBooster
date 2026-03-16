int qemuMonitorJSONGetStatus ( qemuMonitorPtr mon , bool * running , virDomainPausedReason * reason ) {
 int ret ;
 const char * status ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr data ;
 if ( reason ) * reason = VIR_DOMAIN_PAUSED_UNKNOWN ;
 if ( ! ( cmd = qemuMonitorJSONMakeCommand ( "query-status" , NULL ) ) ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret < 0 ) goto cleanup ;
 ret = - 1 ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "query-status reply was missing return data" ) ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetBoolean ( data , "running" , running ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "query-status reply was missing running state" ) ) ;
 goto cleanup ;
 }
 if ( ( status = virJSONValueObjectGetString ( data , "status" ) ) ) {
 if ( ! * running && reason ) * reason = qemuMonitorVMStatusToPausedReason ( status ) ;
 }
 else if ( ! * running ) {
 VIR_DEBUG ( "query-status reply was missing status details" ) ;
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }