static int qemuAgentIOProcessLine ( qemuAgentPtr mon , const char * line , qemuAgentMessagePtr msg ) {
 virJSONValuePtr obj = NULL ;
 int ret = - 1 ;
 VIR_DEBUG ( "Line [%s]" , line ) ;
 if ( ! ( obj = virJSONValueFromString ( line ) ) ) {
 if ( msg && msg -> sync && msg -> first ) {
 VIR_DEBUG ( "Received garbage on sync" ) ;
 msg -> finished = 1 ;
 return 0 ;
 }
 goto cleanup ;
 }
 if ( obj -> type != VIR_JSON_TYPE_OBJECT ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Parsed JSON reply '%s' isn't an object" ) , line ) ;
 goto cleanup ;
 }
 if ( virJSONValueObjectHasKey ( obj , "QMP" ) == 1 ) {
 ret = 0 ;
 }
 else if ( virJSONValueObjectHasKey ( obj , "event" ) == 1 ) {
 ret = qemuAgentIOProcessEvent ( mon , obj ) ;
 }
 else if ( virJSONValueObjectHasKey ( obj , "error" ) == 1 || virJSONValueObjectHasKey ( obj , "return" ) == 1 ) {
 if ( msg ) {
 if ( msg -> sync ) {
 unsigned long long id ;
 if ( virJSONValueObjectGetNumberUlong ( obj , "return" , & id ) < 0 ) {
 VIR_DEBUG ( "Ignoring delayed reply on sync" ) ;
 ret = 0 ;
 goto cleanup ;
 }
 VIR_DEBUG ( "Guest returned ID: %llu" , id ) ;
 if ( msg -> id != id ) {
 VIR_DEBUG ( "Guest agent returned ID: %llu instead of %llu" , id , msg -> id ) ;
 ret = 0 ;
 goto cleanup ;
 }
 }
 msg -> rxObject = obj ;
 msg -> finished = 1 ;
 obj = NULL ;
 }
 else {
 VIR_DEBUG ( "Ignoring delayed reply" ) ;
 }
 ret = 0 ;
 }
 else {
 virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Unknown JSON reply '%s'" ) , line ) ;
 }
 cleanup : virJSONValueFree ( obj ) ;
 return ret ;
 }