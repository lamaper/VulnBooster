char * virLogGetOutputs ( void ) {
 size_t i ;
 virBuffer outputbuf = VIR_BUFFER_INITIALIZER ;
 virLogLock ( ) ;
 for ( i = 0 ;
 i < virLogNbOutputs ;
 i ++ ) {
 virLogDestination dest = virLogOutputs [ i ] -> dest ;
 if ( i ) virBufferAddChar ( & outputbuf , ' ' ) ;
 switch ( dest ) {
 case VIR_LOG_TO_SYSLOG : case VIR_LOG_TO_FILE : virBufferAsprintf ( & outputbuf , "%d:%s:%s" , virLogOutputs [ i ] -> priority , virLogDestinationTypeToString ( dest ) , virLogOutputs [ i ] -> name ) ;
 break ;
 default : virBufferAsprintf ( & outputbuf , "%d:%s" , virLogOutputs [ i ] -> priority , virLogDestinationTypeToString ( dest ) ) ;
 }
 }
 virLogUnlock ( ) ;
 if ( virBufferError ( & outputbuf ) ) {
 virBufferFreeAndReset ( & outputbuf ) ;
 return NULL ;
 }
 return virBufferContentAndReset ( & outputbuf ) ;
 }