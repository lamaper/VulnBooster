static const char * virLogPriorityString ( virLogPriority lvl ) {
 switch ( lvl ) {
 case VIR_LOG_DEBUG : return "debug" ;
 case VIR_LOG_INFO : return "info" ;
 case VIR_LOG_WARN : return "warning" ;
 case VIR_LOG_ERROR : return "error" ;
 }
 return "unknown" ;
 }