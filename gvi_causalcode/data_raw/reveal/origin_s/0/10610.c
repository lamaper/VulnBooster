int qemuMonitorJSONAddPCIDisk ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * path ATTRIBUTE_UNUSED , const char * bus ATTRIBUTE_UNUSED , virDomainDevicePCIAddress * guestAddr ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "pci_add not suppported in JSON mode" ) ) ;
 return - 1 ;
 }