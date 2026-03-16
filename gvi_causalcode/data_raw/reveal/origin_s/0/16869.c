static void qemuMonitorJSONHandleWatchdog ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 const char * action ;
 int actionID ;
 if ( ! ( action = virJSONValueObjectGetString ( data , "action" ) ) ) {
 VIR_WARN ( "missing action in watchdog event" ) ;
 }
 if ( action ) {
 if ( ( actionID = qemuMonitorWatchdogActionTypeFromString ( action ) ) < 0 ) {
 VIR_WARN ( "unknown action %s in watchdog event" , action ) ;
 actionID = VIR_DOMAIN_EVENT_WATCHDOG_NONE ;
 }
 }
 else {
 actionID = VIR_DOMAIN_EVENT_WATCHDOG_NONE ;
 }
 qemuMonitorEmitWatchdog ( mon , actionID ) ;
 }