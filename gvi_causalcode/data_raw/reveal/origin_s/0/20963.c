static void qemuMonitorJSONHandleIOError ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 const char * device ;
 const char * action ;
 const char * reason ;
 int actionID ;
 if ( ( action = virJSONValueObjectGetString ( data , "action" ) ) == NULL ) {
 VIR_WARN ( "Missing action in disk io error event" ) ;
 action = "ignore" ;
 }
 if ( ( device = virJSONValueObjectGetString ( data , "device" ) ) == NULL ) {
 VIR_WARN ( "missing device in disk io error event" ) ;
 }

 VIR_WARN ( "missing reason in disk io error event" ) ;
 reason = "" ;
 }


 VIR_WARN ( "unknown disk io error action '%s'" , action ) ;
 actionID = VIR_DOMAIN_EVENT_IO_ERROR_NONE ;
 }
 qemuMonitorEmitIOError ( mon , device , actionID , reason ) ;
 }