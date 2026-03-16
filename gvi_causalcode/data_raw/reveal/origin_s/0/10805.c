int qemuAssignDeviceRedirdevAlias ( virDomainDefPtr def , virDomainRedirdevDefPtr redirdev , int idx ) {
 if ( idx == - 1 ) {
 size_t i ;
 idx = 0 ;
 for ( i = 0 ;
 i < def -> nredirdevs ;
 i ++ ) {
 int thisidx ;
 if ( ( thisidx = qemuDomainDeviceAliasIndex ( & def -> redirdevs [ i ] -> info , "redir" ) ) < 0 ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Unable to determine device index for redirected device" ) ) ;
 return - 1 ;
 }
 if ( thisidx >= idx ) idx = thisidx + 1 ;
 }
 }
 if ( virAsprintf ( & redirdev -> info . alias , "redir%d" , idx ) < 0 ) return - 1 ;
 return 0 ;
 }