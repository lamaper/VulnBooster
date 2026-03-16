int qemuMonitorTextGetBlockStatsInfo ( qemuMonitorPtr mon , const char * dev_name , long long * rd_req , long long * rd_bytes , long long * rd_total_times , long long * wr_req , long long * wr_bytes , long long * wr_total_times , long long * flush_req , long long * flush_total_times , long long * errs ) {
 char * info = NULL ;
 int ret = - 1 ;
 char * dummy ;
 const char * p , * eol ;
 int devnamelen = strlen ( dev_name ) ;
 if ( qemuMonitorHMPCommand ( mon , "info blockstats" , & info ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "'info blockstats' command failed" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( info , "\ninfo " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "'info blockstats' not supported by this qemu" ) ) ;
 goto cleanup ;
 }
 * rd_req = * rd_bytes = - 1 ;
 * wr_req = * wr_bytes = * errs = - 1 ;
 if ( rd_total_times ) * rd_total_times = - 1 ;
 if ( wr_total_times ) * wr_total_times = - 1 ;
 if ( flush_req ) * flush_req = - 1 ;
 if ( flush_total_times ) * flush_total_times = - 1 ;
 p = info ;
 while ( * p ) {
 if ( STRPREFIX ( p , QEMU_DRIVE_HOST_PREFIX ) ) p += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STREQLEN ( p , dev_name , devnamelen ) && p [ devnamelen ] == ':' && p [ devnamelen + 1 ] == ' ' ) {
 eol = strchr ( p , '\n' ) ;
 if ( ! eol ) eol = p + strlen ( p ) ;
 p += devnamelen + 2 ;
 while ( * p ) {
 if ( STRPREFIX ( p , "rd_bytes=" ) ) {
 p += strlen ( "rd_bytes=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , rd_bytes ) == - 1 ) VIR_DEBUG ( "error reading rd_bytes: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "wr_bytes=" ) ) {
 p += strlen ( "wr_bytes=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , wr_bytes ) == - 1 ) VIR_DEBUG ( "error reading wr_bytes: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "rd_operations=" ) ) {
 p += strlen ( "rd_operations=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , rd_req ) == - 1 ) VIR_DEBUG ( "error reading rd_req: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "wr_operations=" ) ) {
 p += strlen ( "wr_operations=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , wr_req ) == - 1 ) VIR_DEBUG ( "error reading wr_req: %s" , p ) ;
 }
 else if ( rd_total_times && STRPREFIX ( p , "rd_total_times_ns=" ) ) {
 p += strlen ( "rd_total_times_ns=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , rd_total_times ) == - 1 ) VIR_DEBUG ( "error reading rd_total_times: %s" , p ) ;
 }
 else if ( wr_total_times && STRPREFIX ( p , "wr_total_times_ns=" ) ) {
 p += strlen ( "wr_total_times_ns=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , wr_total_times ) == - 1 ) VIR_DEBUG ( "error reading wr_total_times: %s" , p ) ;
 }
 else if ( flush_req && STRPREFIX ( p , "flush_operations=" ) ) {
 p += strlen ( "flush_operations=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , flush_req ) == - 1 ) VIR_DEBUG ( "error reading flush_req: %s" , p ) ;
 }
 else if ( flush_total_times && STRPREFIX ( p , "flush_total_times_ns=" ) ) {
 p += strlen ( "flush_total_times_ns=" ) ;
 if ( virStrToLong_ll ( p , & dummy , 10 , flush_total_times ) == - 1 ) VIR_DEBUG ( "error reading flush_total_times: %s" , p ) ;
 }
 else {
 VIR_DEBUG ( "unknown block stat near %s" , p ) ;
 }
 p = strchr ( p , ' ' ) ;
 if ( ! p || p >= eol ) break ;
 p ++ ;
 }
 ret = 0 ;
 goto cleanup ;
 }
 p = strchr ( p , '\n' ) ;
 if ( ! p ) break ;
 p ++ ;
 }
 qemuReportError ( VIR_ERR_INVALID_ARG , _ ( "no stats found for device %s" ) , dev_name ) ;
 cleanup : VIR_FREE ( info ) ;
 return ret ;
 }