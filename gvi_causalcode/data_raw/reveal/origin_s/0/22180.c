int qemuAssignDeviceHostdevAlias ( virDomainDefPtr def , char * * alias , int idx ) {
 if ( idx == - 1 ) {
 size_t i ;
 idx = 0 ;
 for ( i = 0 ;
 i < def -> nhostdevs ;
 i ++ ) {
 int thisidx ;
 if ( ( thisidx = qemuDomainDeviceAliasIndex ( def -> hostdevs [ i ] -> info , "hostdev" ) ) < 0 ) continue ;
 if ( thisidx >= idx ) idx = thisidx + 1 ;
 }
 for ( i = 0 ;
 i < def -> nnets ;
 i ++ ) {
 int thisidx ;
 if ( ( thisidx = qemuDomainDeviceAliasIndex ( & def -> nets [ i ] -> info , "hostdev" ) ) < 0 ) continue ;
 if ( thisidx >= idx ) idx = thisidx + 1 ;
 }
 }
 if ( virAsprintf ( alias , "hostdev%d" , idx ) < 0 ) return - 1 ;
 return 0 ;
 }