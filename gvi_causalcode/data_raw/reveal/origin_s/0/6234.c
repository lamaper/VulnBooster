void virLogSetFromEnv ( void ) {
 const char * debugEnv ;
 if ( virLogInitialize ( ) < 0 ) return ;
 debugEnv = virGetEnvAllowSUID ( "LIBVIRT_DEBUG" ) ;
 if ( debugEnv && * debugEnv ) virLogSetDefaultPriority ( virLogParseDefaultPriority ( debugEnv ) ) ;
 debugEnv = virGetEnvAllowSUID ( "LIBVIRT_LOG_FILTERS" ) ;
 if ( debugEnv && * debugEnv ) virLogSetFilters ( debugEnv ) ;
 debugEnv = virGetEnvAllowSUID ( "LIBVIRT_LOG_OUTPUTS" ) ;
 if ( debugEnv && * debugEnv ) virLogSetOutputs ( debugEnv ) ;
 }