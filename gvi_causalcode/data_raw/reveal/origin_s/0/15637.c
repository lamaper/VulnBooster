int qemuMonitorTextGetBlockExtent ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * dev_name ATTRIBUTE_UNUSED , unsigned long long * extent ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "unable to query block extent with this QEMU" ) ) ;
 return - 1 ;
 }