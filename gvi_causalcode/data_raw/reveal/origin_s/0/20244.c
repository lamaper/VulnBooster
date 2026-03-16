int qemuAgentUpdateCPUInfo ( unsigned int nvcpus , qemuAgentCPUInfoPtr cpuinfo , int ncpuinfo ) {
 size_t i ;
 int nonline = 0 ;
 int nofflinable = 0 ;
 ssize_t cpu0 = - 1 ;
 for ( i = 0 ;
 i < ncpuinfo ;
 i ++ ) {
 if ( cpuinfo [ i ] . id == 0 ) cpu0 = i ;
 if ( cpuinfo [ i ] . online ) nonline ++ ;
 if ( cpuinfo [ i ] . offlinable && cpuinfo [ i ] . online ) nofflinable ++ ;
 if ( ! cpuinfo [ i ] . online && ! cpuinfo [ i ] . offlinable ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Invalid data provided by guest agent" ) ) ;
 return - 1 ;
 }
 }
 if ( nofflinable == nonline && cpu0 >= 0 && cpuinfo [ cpu0 ] . online ) {
 cpuinfo [ cpu0 ] . offlinable = false ;
 nofflinable -- ;
 }
 if ( nvcpus > ncpuinfo ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "guest agent reports less cpu than requested" ) ) ;
 return - 1 ;
 }
 if ( nvcpus < nonline - nofflinable ) {
 virReportError ( VIR_ERR_INVALID_ARG , "%s" , _ ( "Cannot offline enough CPUs" ) ) ;
 return - 1 ;
 }
 for ( i = 0 ;
 i < ncpuinfo ;
 i ++ ) {
 if ( nvcpus < nonline ) {
 if ( cpuinfo [ i ] . offlinable && cpuinfo [ i ] . online ) {
 cpuinfo [ i ] . online = false ;
 cpuinfo [ i ] . modified = true ;
 nonline -- ;
 }
 }
 else if ( nvcpus > nonline ) {
 if ( ! cpuinfo [ i ] . online ) {
 cpuinfo [ i ] . online = true ;
 cpuinfo [ i ] . modified = true ;
 nonline ++ ;
 }
 }
 else {
 break ;
 }
 }
 return 0 ;
 }