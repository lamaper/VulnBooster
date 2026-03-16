char * qemuAliasFromHostdev ( const virDomainHostdevDef * hostdev ) {
 char * ret ;
 if ( ! hostdev -> info -> alias ) {
 virReportError ( VIR_ERR_INVALID_ARG , "%s" , _ ( "hostdev does not have an alias" ) ) ;
 return NULL ;
 }
 ignore_value ( virAsprintf ( & ret , "%s-%s" , virDomainDeviceAddressTypeToString ( hostdev -> info -> type ) , hostdev -> info -> alias ) ) ;
 return ret ;
 }