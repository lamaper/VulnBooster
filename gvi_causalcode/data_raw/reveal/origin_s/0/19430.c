int qemuAssignDeviceMemoryAlias ( virDomainDefPtr def , virDomainMemoryDefPtr mem ) {
 size_t i ;
 int maxidx = 0 ;
 int idx ;
 for ( i = 0 ;
 i < def -> nmems ;
 i ++ ) {
 if ( ( idx = qemuDomainDeviceAliasIndex ( & def -> mems [ i ] -> info , "dimm" ) ) >= maxidx ) maxidx = idx + 1 ;
 }
 if ( virAsprintf ( & mem -> info . alias , "dimm%d" , maxidx ) < 0 ) return - 1 ;
 return 0 ;
 }