int qemuMonitorJSONGetAllPCIAddresses ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , qemuMonitorPCIAddress * * addrs ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "query-pci not suppported in JSON mode" ) ) ;
 return - 1 ;
 }