static ssize_t qemuGetNextChrDevIndex ( virDomainDefPtr def , virDomainChrDefPtr chr , const char * prefix ) {
 const virDomainChrDef * * arrPtr ;
 size_t cnt ;
 size_t i ;
 ssize_t idx = 0 ;
 const char * prefix2 = NULL ;
 if ( chr -> deviceType == VIR_DOMAIN_CHR_DEVICE_TYPE_CONSOLE ) prefix2 = "serial" ;
 virDomainChrGetDomainPtrs ( def , chr -> deviceType , & arrPtr , & cnt ) ;
 for ( i = 0 ;
 i < cnt ;
 i ++ ) {
 ssize_t thisidx ;
 if ( ( ( thisidx = qemuDomainDeviceAliasIndex ( & arrPtr [ i ] -> info , prefix ) ) < 0 ) && ( prefix2 && ( thisidx = qemuDomainDeviceAliasIndex ( & arrPtr [ i ] -> info , prefix2 ) ) < 0 ) ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unable to determine device index for character device" ) ) ;
 return - 1 ;
 }
 if ( thisidx >= idx ) idx = thisidx + 1 ;
 }
 return idx ;
 }