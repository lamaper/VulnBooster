int qemuMonitorJSONRemovePCIDevice ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , virDomainDevicePCIAddress * guestAddr ATTRIBUTE_UNUSED ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "pci_del not suppported in JSON mode" ) ) ;
 return - 1 ;
 }