int qemuAssignDeviceControllerAlias ( virDomainDefPtr domainDef , virQEMUCapsPtr qemuCaps , virDomainControllerDefPtr controller ) {
 const char * prefix = virDomainControllerTypeToString ( controller -> type ) ;
 if ( controller -> type == VIR_DOMAIN_CONTROLLER_TYPE_PCI ) {
 if ( ! virQEMUCapsHasPCIMultiBus ( qemuCaps , domainDef ) ) {
 return VIR_STRDUP ( controller -> info . alias , "pci" ) ;
 }
 else if ( controller -> model == VIR_DOMAIN_CONTROLLER_MODEL_PCIE_ROOT ) {
 return virAsprintf ( & controller -> info . alias , "pcie.%d" , controller -> idx ) ;
 }
 return virAsprintf ( & controller -> info . alias , "pci.%d" , controller -> idx ) ;
 }
 else if ( controller -> type == VIR_DOMAIN_CONTROLLER_TYPE_IDE ) {
 if ( qemuDomainMachineHasBuiltinIDE ( domainDef ) && controller -> idx == 0 ) return VIR_STRDUP ( controller -> info . alias , "ide" ) ;
 }
 else if ( controller -> type == VIR_DOMAIN_CONTROLLER_TYPE_SATA ) {
 if ( qemuDomainMachineIsQ35 ( domainDef ) && controller -> idx == 0 ) return VIR_STRDUP ( controller -> info . alias , "ide" ) ;
 }
 else if ( controller -> type == VIR_DOMAIN_CONTROLLER_TYPE_USB ) {
 if ( controller -> idx == 0 ) return VIR_STRDUP ( controller -> info . alias , "usb" ) ;
 }
 return virAsprintf ( & controller -> info . alias , "%s%d" , prefix , controller -> idx ) ;
 }