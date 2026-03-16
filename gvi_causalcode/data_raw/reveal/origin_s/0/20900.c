int qemuMonitorTextGetBlockStatsParamsNumber ( qemuMonitorPtr mon , int * nparams ) {
 char * info = NULL ;
 int ret = - 1 ;
 int num = 0 ;
 const char * p , * eol ;
 if ( qemuMonitorHMPCommand ( mon , "info blockstats" , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "'info blockstats' command failed" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( info , "\ninfo " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "'info blockstats' not supported by this qemu" ) ) ;
 goto cleanup ;
 }
 p = info ;
 eol = strchr ( p , '\n' ) ;
 if ( ! eol ) eol = p + strlen ( p ) ;
 p = strchr ( p , ' ' ) ;
 while ( p && p < eol ) {
 if ( STRPREFIX ( p , " rd_bytes=" ) || STRPREFIX ( p , " wr_bytes=" ) || STRPREFIX ( p , " rd_operations=" ) || STRPREFIX ( p , " wr_operations=" ) || STRPREFIX ( p , " rd_total_times_ns=" ) || STRPREFIX ( p , " wr_total_times_ns=" ) || STRPREFIX ( p , " flush_operations=" ) || STRPREFIX ( p , " flush_total_times_ns=" ) ) {
 num ++ ;
 }
 else {
 VIR_DEBUG ( "unknown block stat near %s" , p ) ;
 }
 p = strchr ( p + 1 , ' ' ) ;
 }
 * nparams = num ;
 ret = 0 ;
 cleanup : VIR_FREE ( info ) ;
 return ret ;
 }