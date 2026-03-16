static int qemuAgentIOProcessEvent ( qemuAgentPtr mon , virJSONValuePtr obj ) {
 const char * type ;
 VIR_DEBUG ( "mon=%p obj=%p" , mon , obj ) ;
 type = virJSONValueObjectGetString ( obj , "event" ) ;
 if ( ! type ) {
 VIR_WARN ( "missing event type in message" ) ;
 errno = EINVAL ;
 return - 1 ;
 }
 return 0 ;
 }