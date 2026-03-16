int qemuMonitorTextGetBlockInfo ( qemuMonitorPtr mon , const char * devname , struct qemuDomainDiskInfo * info ) {
 char * reply = NULL ;
 int ret = - 1 ;
 char * dummy ;
 const char * p , * eol ;
 int devnamelen = strlen ( devname ) ;
 int tmp ;
 if ( qemuMonitorHMPCommand ( mon , "info block" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "info block command failed" ) ) ;
 goto cleanup ;
 }
 if ( strstr ( reply , "\ninfo " ) ) {
 qemuReportError ( VIR_ERR_OPERATION_INVALID , "%s" , _ ( "info block not supported by this qemu" ) ) ;
 goto cleanup ;
 }
 p = reply ;
 while ( * p ) {
 if ( STRPREFIX ( p , QEMU_DRIVE_HOST_PREFIX ) ) p += strlen ( QEMU_DRIVE_HOST_PREFIX ) ;
 if ( STREQLEN ( p , devname , devnamelen ) && p [ devnamelen ] == ':' && p [ devnamelen + 1 ] == ' ' ) {
 eol = strchr ( p , '\n' ) ;
 if ( ! eol ) eol = p + strlen ( p ) ;
 p += devnamelen + 2 ;
 while ( * p ) {
 if ( STRPREFIX ( p , "removable=" ) ) {
 p += strlen ( "removable=" ) ;
 if ( virStrToLong_i ( p , & dummy , 10 , & tmp ) == - 1 ) VIR_DEBUG ( "error reading removable: %s" , p ) ;
 else info -> removable = ( tmp != 0 ) ;
 }
 else if ( STRPREFIX ( p , "locked=" ) ) {
 p += strlen ( "locked=" ) ;
 if ( virStrToLong_i ( p , & dummy , 10 , & tmp ) == - 1 ) VIR_DEBUG ( "error reading locked: %s" , p ) ;
 else info -> locked = ( tmp != 0 ) ;
 }
 else if ( STRPREFIX ( p , "tray_open=" ) ) {
 p += strlen ( "tray_open=" ) ;
 if ( virStrToLong_i ( p , & dummy , 10 , & tmp ) == - 1 ) VIR_DEBUG ( "error reading tray_open: %s" , p ) ;
 else info -> tray_open = ( tmp != 0 ) ;
 }
 else {
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
 qemuReportError ( VIR_ERR_INVALID_ARG , _ ( "no info for device '%s'" ) , devname ) ;
 cleanup : VIR_FREE ( reply ) ;
 return ret ;
 }