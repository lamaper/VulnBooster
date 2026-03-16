int qemuMonitorJSONSetCPU ( qemuMonitorPtr mon , int cpu , int online ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "cpu_set" , "U:cpu" , ( unsigned long long ) cpu , "s:state" , online ? "online" : "offline" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "cpu_set" ) ) {
 VIR_DEBUG ( "cpu_set command not found, trying HMP" ) ;
 ret = qemuMonitorTextSetCPU ( mon , cpu , online ) ;
 goto cleanup ;
 }
 if ( ret == 0 ) {


 if ( ret == 0 ) ret = 1 ;
 }
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }