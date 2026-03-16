int qemuMonitorJSONSetDrivePassphrase ( qemuMonitorPtr mon , const char * alias , const char * passphrase ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 char * drive ;
 if ( virAsprintf ( & drive , "%s%s" , QEMU_DRIVE_HOST_PREFIX , alias ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 cmd = qemuMonitorJSONMakeCommand ( "block_passwd" , "s:device" , drive , "s:password" , passphrase , NULL ) ;
 VIR_FREE ( drive ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }