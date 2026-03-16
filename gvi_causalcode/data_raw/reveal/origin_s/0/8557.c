int qemuMonitorJSONAddPCINetwork ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * nicstr ATTRIBUTE_UNUSED , virDomainDevicePCIAddress * guestAddr ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "pci_add not suppported in JSON mode" ) ) ;
 return - 1 ;
 }