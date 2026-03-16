int qemuMonitorTextAddUSBDeviceExact ( qemuMonitorPtr mon , int bus , int dev ) {
 int ret ;
 char * addr ;
 if ( virAsprintf ( & addr , "host:%.3d.%.3d" , bus , dev ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 ret = qemuMonitorTextAddUSBDevice ( mon , addr ) ;
 VIR_FREE ( addr ) ;
 return ret ;
 }