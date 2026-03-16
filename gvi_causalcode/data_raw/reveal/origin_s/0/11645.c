static int qemuMonitorJSONIOProcessLine ( qemuMonitorPtr mon , const char * line , qemuMonitorMessagePtr msg ) {
 virJSONValuePtr obj = NULL ;
 int ret = - 1 ;
 VIR_DEBUG ( "Line [%s]" , line ) ;
 if ( ! ( obj = virJSONValueFromString ( line ) ) ) goto cleanup ;
 if ( obj -> type != VIR_JSON_TYPE_OBJECT ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Parsed JSON reply '%s' isn't an object" ) , line ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectHasKey ( obj , "QMP" ) == 1 ) {
 ret = 0 ;
 }
 else if ( virJSONValueObjectHasKey ( obj , "event" ) == 1 ) {
 PROBE ( QEMU_MONITOR_RECV_EVENT , "mon=%p event=%s" , mon , line ) ;
 ret = qemuMonitorJSONIOProcessEvent ( mon , obj ) ;
 }
 else if ( virJSONValueObjectHasKey ( obj , "error" ) == 1 || virJSONValueObjectHasKey ( obj , "return" ) == 1 ) {
 PROBE ( QEMU_MONITOR_RECV_REPLY , "mon=%p reply=%s" , mon , line ) ;
 if ( msg ) {
 msg -> rxObject = obj ;
 msg -> finished = 1 ;
 obj = NULL ;
 ret = 0 ;
 }
 else {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Unexpected JSON reply '%s'" ) , line ) ;
 }
 }
 else {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Unknown JSON reply '%s'" ) , line ) ;
 }
 cleanup : virJSONValueFree ( obj ) ;
 return ret ;
 }