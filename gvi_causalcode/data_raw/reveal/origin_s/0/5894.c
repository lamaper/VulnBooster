static void virLogResetFilters ( void ) {
 virLogFilterListFree ( virLogFilters , virLogNbFilters ) ;
 virLogFilters = NULL ;
 virLogNbFilters = 0 ;
 virLogFiltersSerial ++ ;
 }