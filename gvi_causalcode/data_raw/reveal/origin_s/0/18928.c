int qemuMonitorJSONAddNetdev ( qemuMonitorPtr mon , const char * netdevstr ) {
 int ret = - 1 ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 virJSONValuePtr args = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "netdev_add" , NULL ) ;
 if ( ! cmd ) return - 1 ;
 args = qemuMonitorJSONKeywordStringToJSON ( netdevstr , "type" ) ;
 if ( ! args ) goto cleanup ;
 if ( virJSONValueObjectAppend ( cmd , "arguments" , args ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 args = NULL ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( args ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }