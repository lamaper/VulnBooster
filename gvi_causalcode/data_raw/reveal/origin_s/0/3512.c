static int qemuMonitorTextAddUSBDevice ( qemuMonitorPtr mon , const char * addr ) {
 char * cmd ;
 char * reply = NULL ;
 int ret = - 1 ;
 if ( virAsprintf ( & cmd , "usb_add %s" , addr ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 if ( qemuMonitorHMPCommand ( mon , cmd , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "cannot attach usb device" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "Could not add " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "adding usb device failed" ) ) ;
 goto cleanup ;
 }
 ret = 0 ;
 cleanup : VIR_FREE ( cmd ) ;
 VIR_FREE ( reply ) ;
 return ret ;
 }