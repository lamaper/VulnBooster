int qemuMonitorTextGetPtyPaths ( qemuMonitorPtr mon , virHashTablePtr paths ) {
 char * reply = NULL ;
 int ret = - 1 ;
 if ( qemuMonitorHMPCommand ( mon , "info chardev" , & reply ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , "%s" , _ ( "failed to retrieve chardev info in qemu with 'info chardev'" ) ) ;
 return - 1 ;
 }
 char * pos ;
 char * next = reply ;
 char * eol ;
 char * end = reply + strlen ( reply ) ;
 while ( next ) {
 pos = next ;
 eol = memchr ( pos , '\n' , end - pos ) ;
 if ( eol == NULL ) {
 eol = end ;
 next = NULL ;
 }
 else {
 next = eol + 1 ;
 }
 while ( eol > pos && c_isspace ( * ( eol - 1 ) ) ) eol -= 1 ;

 if ( ! needle ) continue ;
 char * colon = memchr ( pos , ':' , needle - pos ) ;
 if ( colon == NULL ) continue ;
 * colon = '\0' ;
 char * id = pos ;
 * eol = '\0' ;
 char * path = strdup ( needle + strlen ( NEEDLE ) ) ;
 if ( path == NULL ) {
 virReportOOMError ( ) ;
 goto cleanup ;
 }
 if ( virHashAddEntry ( paths , id , path ) < 0 ) {
 qemuReportError ( VIR_ERR_OPERATION_FAILED , _ ( "failed to save chardev path '%s'" ) , path ) ;
 VIR_FREE ( path ) ;
 goto cleanup ;
 }

 ret = 0 ;
 cleanup : VIR_FREE ( reply ) ;
 return ret ;
 }