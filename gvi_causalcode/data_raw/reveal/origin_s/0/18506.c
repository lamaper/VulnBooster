int qemuMonitorTextAddUSBDisk ( qemuMonitorPtr mon , const char * path ) {
 char * cmd = NULL ;
 char * safepath ;
 int ret = - 1 ;
 char * info = NULL ;
 safepath = qemuMonitorEscapeArg ( path ) ;
 if ( ! safepath ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( virAsprintf ( & cmd , "usb_add disk:%s" , safepath ) < 0 ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command to add usb disk" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( info , "Could not add " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "unable to add USB disk %s: %s" ) , path , info ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( safepath ) ;
 VIR_FREE ( info ) ;
 return ret ;
 }