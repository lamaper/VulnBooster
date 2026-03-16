static void virLogSourceUpdate ( virLogSourcePtr source ) {
 virLogLock ( ) ;
 if ( source -> serial < virLogFiltersSerial ) {
 unsigned int priority = virLogDefaultPriority ;
 unsigned int flags = 0 ;
 size_t i ;
 for ( i = 0 ;
 i < virLogNbFilters ;
 i ++ ) {
 if ( strstr ( source -> name , virLogFilters [ i ] -> match ) ) {
 priority = virLogFilters [ i ] -> priority ;
 flags = virLogFilters [ i ] -> flags ;
 break ;
 }
 }
 source -> priority = priority ;
 source -> flags = flags ;
 source -> serial = virLogFiltersSerial ;
 }
 virLogUnlock ( ) ;
 }