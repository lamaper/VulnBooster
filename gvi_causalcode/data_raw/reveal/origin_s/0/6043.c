int qemuMonitorTextAddUSBDeviceMatch ( qemuMonitorPtr mon , int vendor , int product ) {
 int ret ;
 char * addr ;
 if ( virAsprintf ( & addr , "host:%.4x:%.4x" , vendor , product ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 ret = qemuMonitorTextAddUSBDevice ( mon , addr ) ;
 VIR_FREE ( addr ) ;
 return ret ;
 }