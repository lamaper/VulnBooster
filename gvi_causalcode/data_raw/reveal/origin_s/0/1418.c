int virLogDefineFilters ( virLogFilterPtr * filters , size_t nfilters ) {
 if ( virLogInitialize ( ) < 0 ) return - 1 ;
 virLogLock ( ) ;
 virLogResetFilters ( ) ;
 virLogFilters = filters ;
 virLogNbFilters = nfilters ;
 virLogUnlock ( ) ;
 return 0 ;
 }