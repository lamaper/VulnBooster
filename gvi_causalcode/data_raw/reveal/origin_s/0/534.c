int qemuMonitorTextSetMigrationDowntime ( qemuMonitorPtr mon , unsigned long long downtime ) {
 char * cmd = NULL ;
 char * info = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "migrate_set_downtime %llums" , downtime ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "could not set maximum migration downtime" ) ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( info ) ;
 VIR_FREE ( cmd ) ;
 return ret ;
 }