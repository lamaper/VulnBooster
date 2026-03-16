int qemuMonitorJSONAddUSBDeviceExact ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , int bus ATTRIBUTE_UNUSED , int dev ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "usb_add not suppported in JSON mode" ) ) ;
 return - 1 ;
 }