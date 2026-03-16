int qemuMonitorJSONGetBalloonInfo ( qemuMonitorPtr mon , unsigned long * currmem ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-balloon" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 * currmem = 0 ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) {
 if ( qemuMonitorJSONHasError ( reply , "DeviceNotActive" ) || qemuMonitorJSONHasError ( reply , "KVMMissingCap" ) ) goto cleanup ;
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 ) {
 virJSONValuePtr data ;
 unsigned long long mem ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing return data" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 if ( virJSONValueObjectGetNumberUlong ( data , "actual" , & mem ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "info balloon reply was missing balloon data" ) ) ;
 ret = - 1 ;
 goto cleanup ;
 }
 * currmem = ( mem / 1024 ) ;
 ret = 1 ;
 }
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }