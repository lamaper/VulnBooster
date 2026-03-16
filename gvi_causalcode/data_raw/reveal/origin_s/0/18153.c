char * qemuDomainGetSecretAESAlias ( const char * srcalias , bool isLuks ) {
 char * alias ;
 if ( ! srcalias ) {
 virReportError ( VIR_ERR_INVALID_ARG , "%s" , _ ( "encrypted secret alias requires valid source alias" ) ) ;
 return NULL ;
 }
 if ( isLuks ) ignore_value ( virAsprintf ( & alias , "%s-luks-secret0" , srcalias ) ) ;
 else ignore_value ( virAsprintf ( & alias , "%s-secret0" , srcalias ) ) ;
 return alias ;
 }