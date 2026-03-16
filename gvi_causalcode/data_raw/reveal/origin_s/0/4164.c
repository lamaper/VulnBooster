static int virLogOnceInit ( void ) {
 if ( virMutexInit ( & virLogMutex ) < 0 ) return - 1 ;
 virLogLock ( ) ;
 virLogDefaultPriority = VIR_LOG_DEFAULT ;
 if ( VIR_ALLOC_QUIET ( virLogRegex ) >= 0 ) {
 if ( regcomp ( virLogRegex , VIR_LOG_REGEX , REG_EXTENDED ) != 0 ) VIR_FREE ( virLogRegex ) ;
 }
 virLogHostname = virGetHostnameQuiet ( ) ;
 virLogUnlock ( ) ;
 return 0 ;
 }