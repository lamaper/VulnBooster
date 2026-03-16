int qemuMonitorTextSetMigrationSpeed ( qemuMonitorPtr mon , unsigned long bandwidth ) {
 char * cmd = NULL ;
 char * info = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "migrate_set_speed %lum" , bandwidth ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not restrict migration speed" ) ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( info ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }