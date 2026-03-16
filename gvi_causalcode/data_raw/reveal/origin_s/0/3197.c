char * qemuDomainGetMasterKeyAlias ( void ) {
 char * alias ;
 ignore_value ( VIR_STRDUP ( alias , "masterKey0" ) ) ;
 return alias ;
 }