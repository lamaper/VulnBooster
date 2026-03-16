static int qemuMonitorJSONIOProcessEvent ( qemuMonitorPtr mon , virJSONValuePtr obj ) {
 const char * type ;
 int i ;
 VIR_DEBUG ( "mon=%p obj=%p" , mon , obj ) ;
 type = virJSONValueObjectGetString ( obj , "event" ) ;
 if ( ! type ) {
 VIR_WARN ( "missing event type in message" ) ;
 errno = EINVAL ;
 return - 1 ;
 }
 for ( i = 0 ;
 i < ARRAY_CARDINALITY ( eventHandlers ) ;
 i ++ ) {
 if ( STREQ ( eventHandlers [ i ] . type , type ) ) {
 virJSONValuePtr data = virJSONValueObjectGet ( obj , "data" ) ;
 VIR_DEBUG ( "handle %s handler=%p data=%p" , type , eventHandlers [ i ] . handler , data ) ;
 ( eventHandlers [ i ] . handler ) ( mon , data ) ;
 break ;
 }
 }
 return 0 ;
 }