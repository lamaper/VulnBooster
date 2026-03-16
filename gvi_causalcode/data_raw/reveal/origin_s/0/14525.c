static int qemuMonitorTextSaveMemory ( qemuMonitorPtr mon , const char * cmdtype , unsigned long long offset , size_t length , const char * path ) {
 char * cmd = NULL ;
 char * reply = NULL ;
 char * safepath = NULL ;
 int ret = - 1 ;
 if ( ! ( safepath = qemuMonitorEscapeArg ( path ) ) ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virAsprintf ( & cmd , "%s %llu %zi \"%s\"" , cmdtype , offset , length , safepath ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "could not save memory region to '%s'" ) , path ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 VIR_FREE ( safepath ) ;
 return ret ;
 }