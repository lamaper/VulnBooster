int qemuMonitorTextStartCPUs ( qemuMonitorPtr mon , virConnectPtr conn ) {
 char * reply ;
 if ( qemuMonitorTextCommandWithHandler ( mon , "cont" , qemuMonitorSendDiskPassphrase , conn , - 1 , & reply ) < 0 ) return - 1 ;
 VIR_FREE ( reply ) ;
 return 0 ;
 }