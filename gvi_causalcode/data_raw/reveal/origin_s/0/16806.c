int qemuMonitorJSONSendKey ( qemuMonitorPtr mon , unsigned int holdtime , unsigned int * keycodes , unsigned int nkeycodes ) {
 if ( qemuMonitorCheckHMP ( mon , "sendkey" ) ) {
 return qemuMonitorTextSendKey ( mon , holdtime , keycodes , nkeycodes ) ;
 }
 else return - 1 ;
 }