static int qemuMonitorSendDiskPassphrase ( qemuMonitorPtr mon , qemuMonitorMessagePtr msg , const char * data , size_t len ATTRIBUTE_UNUSED , void * opaque ) {
 virConnectPtr conn = opaque ;
 char * path ;
 char * passphrase = NULL ;
 size_t passphrase_len = 0 ;
 int res ;
 const char * pathStart ;
 const char * pathEnd ;
 pathStart = strstr ( data , DISK_ENCRYPTION_PREFIX ) ;
 pathEnd = strstr ( data , DISK_ENCRYPTION_POSTFIX ) ;
 if ( ! pathStart || ! pathEnd || pathStart >= pathEnd ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "Unable to extract disk path from %s" ) , data ) ;
 return - 1 ;
 }
 pathStart += strlen ( DISK_ENCRYPTION_PREFIX ) ;
 if ( ! ( path = strndup ( pathStart , pathEnd - pathStart ) ) ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 res = qemuMonitorGetDiskSecret ( mon , conn , path , & passphrase , & passphrase_len ) ;
 VIR_FREE ( path ) ;
 if ( res < 0 ) return - 1 ;
 if ( VIR_REALLOC_N ( msg -> txBuffer , msg -> txLength + passphrase_len + 1 + 1 ) < 0 ) {
 memset ( passphrase , 0 , passphrase_len ) ;
 VIR_FREE ( passphrase ) ;
 virReportOOMError ( ) ;
 return - 1 ;
 }
 memcpy ( msg -> txBuffer + msg -> txLength , passphrase , passphrase_len ) ;
 msg -> txLength += passphrase_len ;
 msg -> txBuffer [ msg -> txLength ] = '\r' ;
 msg -> txLength ++ ;
 msg -> txBuffer [ msg -> txLength ] = '\0' ;
 memset ( passphrase , 0 , passphrase_len ) ;
 VIR_FREE ( passphrase ) ;
 return 0 ;
 }