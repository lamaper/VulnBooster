int qemuAssignDeviceDiskAlias ( virDomainDefPtr def , virDomainDiskDefPtr disk , virQEMUCapsPtr qemuCaps ) {
 const char * prefix = virDomainDiskBusTypeToString ( disk -> bus ) ;
 int controllerModel = - 1 ;
 if ( disk -> info . type == VIR_DOMAIN_DEVICE_ADDRESS_TYPE_DRIVE ) {
 if ( disk -> bus == VIR_DOMAIN_DISK_BUS_SCSI ) {
 controllerModel = virDomainDeviceFindControllerModel ( def , & disk -> info , VIR_DOMAIN_CONTROLLER_TYPE_SCSI ) ;
 if ( ( qemuDomainSetSCSIControllerModel ( def , qemuCaps , & controllerModel ) ) < 0 ) return - 1 ;
 }
 if ( disk -> bus != VIR_DOMAIN_DISK_BUS_SCSI || controllerModel == VIR_DOMAIN_CONTROLLER_MODEL_SCSI_LSILOGIC ) {
 if ( virAsprintf ( & disk -> info . alias , "%s%d-%d-%d" , prefix , disk -> info . addr . drive . controller , disk -> info . addr . drive . bus , disk -> info . addr . drive . unit ) < 0 ) return - 1 ;
 }
 else {
 if ( virAsprintf ( & disk -> info . alias , "%s%d-%d-%d-%d" , prefix , disk -> info . addr . drive . controller , disk -> info . addr . drive . bus , disk -> info . addr . drive . target , disk -> info . addr . drive . unit ) < 0 ) return - 1 ;
 }
 }
 else {
 int idx = virDiskNameToIndex ( disk -> dst ) ;
 if ( virAsprintf ( & disk -> info . alias , "%s-disk%d" , prefix , idx ) < 0 ) return - 1 ;
 }
 return 0 ;
 }