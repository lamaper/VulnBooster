int qemuMonitorJSONCheckHMP ( qemuMonitorPtr mon ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "query-commands" , NULL ) ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr data ;
 int i , n ;
 if ( ! cmd ) return ret ;
 if ( qemuMonitorJSONCommand ( mon , cmd , & reply ) < 0 || qemuMonitorJSONCheckError ( cmd , reply ) < 0 ) goto cleanup ;
 if ( ! ( data = virJSONValueObjectGet ( reply , "return" ) ) || data -> type != VIR_JSON_TYPE_ARRAY || ( n = virJSONValueArraySize ( data ) ) <= 0 ) goto cleanup ;
 for ( i = 0 ;
 i < n ;
 i ++ ) {
 virJSONValuePtr entry ;
 const char * name ;
 if ( ! ( entry = virJSONValueArrayGet ( data , i ) ) || ! ( name = virJSONValueObjectGetString ( entry , "name" ) ) ) goto cleanup ;
 if ( STREQ ( name , "human-monitor-command" ) ) {
 ret = 1 ;
 goto cleanup ;
 }
 }
 ret = 0 ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }