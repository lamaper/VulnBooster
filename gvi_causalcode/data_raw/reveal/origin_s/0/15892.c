int qemuMonitorJSONAddUSBDisk ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * path ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "usb_add not suppported in JSON mode" ) ) ;
 return - 1 ;
 }