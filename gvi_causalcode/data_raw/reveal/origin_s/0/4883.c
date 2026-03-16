int qemuMonitorJSONAttachDrive ( qemuMonitorPtr mon , const char * drivestr , virDomainDevicePCIAddress * controllerAddr , virDomainDeviceDriveAddress * driveAddr ) {
 int ret ;
 virJSONValuePtr cmd = NULL ;
 virJSONValuePtr reply = NULL ;
 char * dev ;
 if ( virAsprintf ( & dev , "%.2x:%.2x.%.1x" , controllerAddr -> bus , controllerAddr -> slot , controllerAddr -> function ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 cmd = qemuMonitorJSONMakeCommand ( "drive_add" , "s:pci_addr" , dev , "s:opts" , drivestr , NULL ) ;
 VIR_FREE ( dev ) ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 if ( ret == 0 && qemuMonitorJSONGetGuestDriveAddress ( reply , driveAddr ) < 0 ) ret = - 1 ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }