int qemuMonitorTextMigrate ( qemuMonitorPtr mon , unsigned int flags , const char * dest ) {
 char * cmd = NULL ;
 char * info = NULL ;
 int ret = - 1 ;
 char * safedest = qemuMonitorEscapeArg ( dest ) ;
 virBuffer extra = VIR_BUFFER_INITIALIZER ;
 char * extrastr = NULL ;
 if ( ! safedest ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( flags & QEMU_MONITOR_MIGRATE_BACKGROUND ) virBufferAddLit ( & extra , " -d" ) ;
 if ( flags & QEMU_MONITOR_MIGRATE_NON_SHARED_DISK ) virBufferAddLit ( & extra , " -b" ) ;
 if ( flags & QEMU_MONITOR_MIGRATE_NON_SHARED_INC ) virBufferAddLit ( & extra , " -i" ) ;
 if ( virBufferError ( & extra ) ) {
 virBufferFreeAndReset ( & extra ) ;
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 extrastr = virBufferContentAndReset ( & extra ) ;
 if ( virAsprintf ( & cmd , "migrate %s\"%s\"" , extrastr ? extrastr : "" , safedest ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to start migration to %s" ) , dest ) ;
 goto cleanup ;
 }
 if ( strstr ( info , "fail" ) != NULL ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "migration to '%s' failed: %s" ) , dest , info ) ;
 goto cleanup ;
 }
 if ( strstr ( info , "unknown command:" ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , _ ( "migration to '%s' not supported by this qemu: %s" ) , dest , info ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( extrastr ) ;
 VIR_FREE ( safedest ) ;
 VIR_FREE ( info ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }