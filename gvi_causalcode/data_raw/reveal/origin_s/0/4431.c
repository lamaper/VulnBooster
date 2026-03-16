static int qemuMonitorTextParseBlockIoThrottle ( const char * result , const char * device , virDomainBlockIoTuneInfoPtr reply ) {
 char * dummy = NULL ;
 int ret = - 1 ;
 const char * p , * eol ;
 int devnamelen = strlen ( device ) ;
 p = result ;
 while ( * p ) {
 if ( STRPREFIX ( p , QEMU_DRIVE_HOST_PREFIX ) ) p += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STREQLEN ( p , device , devnamelen ) && p [ devnamelen ] == ':' && p [ devnamelen + 1 ] == ' ' ) {
 eol = strchr ( p , '\n' ) ;
 if ( ! eol ) eol = p + strlen ( p ) ;
 p += devnamelen + 2 ;
 while ( * p ) {
 if ( STRPREFIX ( p , "bps=" ) ) {
 p += strlen ( "bps=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> total_bytes_sec ) == - 1 ) VIR_DEBUG ( "error reading total_bytes_sec: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "bps_rd=" ) ) {
 p += strlen ( "bps_rd=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> read_bytes_sec ) == - 1 ) VIR_DEBUG ( "error reading read_bytes_sec: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "bps_wr=" ) ) {
 p += strlen ( "bps_wr=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> write_bytes_sec ) == - 1 ) VIR_DEBUG ( "error reading write_bytes_sec: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "iops=" ) ) {
 p += strlen ( "iops=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> total_iops_sec ) == - 1 ) VIR_DEBUG ( "error reading total_iops_sec: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "iops_rd=" ) ) {
 p += strlen ( "iops_rd=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> read_iops_sec ) == - 1 ) VIR_DEBUG ( "error reading read_iops_sec: %s" , p ) ;
 }
 else if ( STRPREFIX ( p , "iops_wr=" ) ) {
 p += strlen ( "iops_wr=" ) ;
 if ( virStrToLong_ull ( p , & dummy , 10 , & reply -> write_iops_sec ) == - 1 ) VIR_DEBUG ( "error reading write_iops_sec: %s" , p ) ;
 }
 else {
 VIR_DEBUG ( " unknown block info %s" , p ) ;
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
 qemuReportError ( VIR_ERR_INVALID_ARG , _ ( "No info for device '%s'" ) , device ) ;
 cleanup : return ret ;
 }