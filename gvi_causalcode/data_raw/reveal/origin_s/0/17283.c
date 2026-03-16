int qemuMonitorJSONAddUSBDeviceMatch ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , int vendor ATTRIBUTE_UNUSED , int product ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "usb_add not suppported in JSON mode" ) ) ;
 return - 1 ;
 }