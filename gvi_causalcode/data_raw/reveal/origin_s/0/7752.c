static int qemuMonitorSendVNCPassphrase ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , qemuMonitorMessagePtr msg , const char * data ATTRIBUTE_UNUSED , size_t len ATTRIBUTE_UNUSED , void * opaque ) {
 char * passphrase = opaque ;
 size_t passphrase_len = strlen ( passphrase ) ;
 if ( VIR_REALLOC_N ( msg -> txBuffer , msg -> txLength + passphrase_len + 1 + 1 ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 memcpy ( msg -> txBuffer + msg -> txLength , passphrase , passphrase_len ) ;
 msg -> txLength += passphrase_len ;
 msg -> txBuffer [ msg -> txLength ] = '\r' ;
 msg -> txLength ++ ;
 msg -> txBuffer [ msg -> txLength ] = '\0' ;
 return 0 ;
 }