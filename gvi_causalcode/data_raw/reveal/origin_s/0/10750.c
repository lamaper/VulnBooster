int qemuAssignDeviceChrAlias ( virDomainDefPtr def , virDomainChrDefPtr chr , ssize_t idx ) {
 const char * prefix = NULL ;
 switch ( ( virDomainChrDeviceType ) chr -> deviceType ) {
 case VIR_DOMAIN_CHR_DEVICE_TYPE_PARALLEL : prefix = "parallel" ;
 break ;
 case VIR_DOMAIN_CHR_DEVICE_TYPE_SERIAL : prefix = "serial" ;
 break ;
 case VIR_DOMAIN_CHR_DEVICE_TYPE_CONSOLE : prefix = "console" ;
 break ;
 case VIR_DOMAIN_CHR_DEVICE_TYPE_CHANNEL : prefix = "channel" ;
 break ;
 case VIR_DOMAIN_CHR_DEVICE_TYPE_LAST : return - 1 ;
 }
 if ( idx == - 1 && ( idx = qemuGetNextChrDevIndex ( def , chr , prefix ) ) < 0 ) return - 1 ;
 return virAsprintf ( & chr -> info . alias , "%s%zd" , prefix , idx ) ;
 }