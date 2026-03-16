int qemuAssignDeviceNetAlias ( virDomainDefPtr def , virDomainNetDefPtr net , int idx ) {
 if ( networkGetActualType ( net ) == VIR_DOMAIN_NET_TYPE_HOSTDEV ) return qemuAssignDeviceHostdevAlias ( def , & net -> info . alias , - 1 ) ;
 if ( idx == - 1 ) {
 size_t i ;
 idx = 0 ;
 for ( i = 0 ;
 i < def -> nnets ;
 i ++ ) {
 int thisidx ;
 if ( ( thisidx = qemuDomainDeviceAliasIndex ( & def -> nets [ i ] -> info , "net" ) ) < 0 ) continue ;
 if ( thisidx >= idx ) idx = thisidx + 1 ;
 }
 }
 if ( virAsprintf ( & net -> info . alias , "net%d" , idx ) < 0 ) return - 1 ;
 return 0 ;
 }