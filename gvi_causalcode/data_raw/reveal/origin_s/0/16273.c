char * qemuAliasFromDisk ( const virDomainDiskDef * disk ) {
 char * ret ;
 if ( ! disk -> info . alias ) {
 virReportError ( VIR_ERR_INVALID_ARG , "%s" , _ ( "disk does not have an alias" ) ) ;
 return NULL ;
 }
 ignore_value ( virAsprintf ( & ret , "%s%s" , QEMU_DRIVE_HOST_PREFIX , disk -> info . alias ) ) ;
 return ret ;
 }