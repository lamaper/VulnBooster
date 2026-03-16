VIR_ONCE_GLOBAL_INIT ( virLog ) int virLogReset ( void ) {
 if ( virLogInitialize ( ) < 0 ) return - 1 ;
 virLogLock ( ) ;
 virLogResetFilters ( ) ;
 virLogResetOutputs ( ) ;
 virLogDefaultPriority = VIR_LOG_DEFAULT ;
 virLogUnlock ( ) ;
 return 0 ;
 }