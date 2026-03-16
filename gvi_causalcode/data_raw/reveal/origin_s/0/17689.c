int qemuMonitorJSONHumanCommandWithFd ( qemuMonitorPtr mon , const char * cmd_str , int scm_fd , char * * reply_str ) {
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr obj ;
 int ret = - 1 ;
 cmd = qemuMonitorJSONMakeCommand ( "human-monitor-command" , "s:command-line" , cmd_str , NULL ) ;
 if ( ! cmd || qemuMonitorJSONCommandWithFd ( mon , cmd , scm_fd , & reply ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONCheckError ( cmd , reply ) ) goto cleanup ;
 if ( ! ( obj = virJSONValueObjectGet ( reply , "return" ) ) ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "human monitor command was missing return data" ) ) ;
 goto cleanup ;
 }
 if ( reply_str ) {
 const char * data ;
 if ( ( data = virJSONValueGetString ( obj ) ) ) * reply_str = strdup ( data ) ;
 else * reply_str = strdup ( "" ) ;
 if ( ! * reply_str ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }