int qemuAssignDeviceRNGAlias ( virDomainDefPtr def , virDomainRNGDefPtr rng ) {
 size_t i ;
 int maxidx = 0 ;
 int idx ;
 for ( i = 0 ;
 i < def -> nrngs ;
 i ++ ) {
 if ( ( idx = qemuDomainDeviceAliasIndex ( & def -> rngs [ i ] -> info , "rng" ) ) >= maxidx ) maxidx = idx + 1 ;
 }
 if ( virAsprintf ( & rng -> info . alias , "rng%d" , maxidx ) < 0 ) return - 1 ;
 return 0 ;
 }