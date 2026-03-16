char * virLogGetFilters ( void ) {
 size_t i ;
 virBuffer filterbuf = VIR_BUFFER_INITIALIZER ;
 virLogLock ( ) ;
 for ( i = 0 ;
 i < virLogNbFilters ;
 i ++ ) {
 const char * sep = ":" ;
 if ( virLogFilters [ i ] -> flags & VIR_LOG_STACK_TRACE ) sep = ":+" ;
 virBufferAsprintf ( & filterbuf , "%d%s%s " , virLogFilters [ i ] -> priority , sep , virLogFilters [ i ] -> match ) ;
 }
 virLogUnlock ( ) ;
 if ( virBufferError ( & filterbuf ) ) {
 virBufferFreeAndReset ( & filterbuf ) ;
 return NULL ;
 }
 return virBufferContentAndReset ( & filterbuf ) ;
 }