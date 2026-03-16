virLogFilterPtr virLogParseFilter ( const char * src ) {
 virLogFilterPtr ret = NULL ;
 size_t count = 0 ;
 virLogPriority prio ;
 char * * tokens = NULL ;
 unsigned int flags = 0 ;
 char * match = NULL ;
 VIR_DEBUG ( "filter=%s" , src ) ;
 if ( ! ( tokens = virStringSplitCount ( src , ":" , 0 , & count ) ) || count != 2 ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Malformed format for filter '%s'" ) , src ) ;
 goto cleanup ;
 }
 if ( virStrToLong_uip ( tokens [ 0 ] , NULL , 10 , & prio ) < 0 || ( prio < VIR_LOG_DEBUG ) || ( prio > VIR_LOG_ERROR ) ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Invalid priority '%s' for output '%s'" ) , tokens [ 0 ] , src ) ;
 goto cleanup ;
 }
 match = tokens [ 1 ] ;
 if ( match [ 0 ] == '+' ) {
 flags |= VIR_LOG_STACK_TRACE ;
 match ++ ;
 }
 if ( ! * match ) {
 virReportError ( VIR_ERR_INVALID_ARG , _ ( "Invalid match string '%s'" ) , tokens [ 1 ] ) ;
 goto cleanup ;
 }
 if ( ! ( ret = virLogFilterNew ( match , prio , flags ) ) ) goto cleanup ;
 cleanup : virStringListFree ( tokens ) ;
 return ret ;
 }