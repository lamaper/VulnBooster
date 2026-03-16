int qemuMonitorJSONDiskSnapshot ( qemuMonitorPtr mon , const char * device , const char * file ) {
 int ret ;
 virJSONValuePtr cmd ;
 virJSONValuePtr reply = NULL ;
 cmd = qemuMonitorJSONMakeCommand ( "blockdev-snapshot-sync" , "s:device" , device , "s:snapshot-file" , file , NULL ) ;
 if ( ! cmd ) return - 1 ;
 if ( ( ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ) < 0 ) goto cleanup ;
 if ( qemuMonitorJSONHasError ( reply , "CommandNotFound" ) && qemuMonitorCheckHMP ( mon , "snapshot_blkdev" ) ) {
 VIR_DEBUG ( "blockdev-snapshot-sync command not found, trying HMP" ) ;
 ret = qemuMonitorTextDiskSnapshot ( mon , device , file ) ;
 goto cleanup ;
 }
 ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 cleanup : virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }