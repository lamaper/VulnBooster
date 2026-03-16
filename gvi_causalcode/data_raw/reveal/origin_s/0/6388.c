int qemuMonitorTextIOProcess ( qemuMonitorPtr mon ATTRIBUTE_UNUSED , const char * data , size_t len ATTRIBUTE_UNUSED , qemuMonitorMessagePtr msg ) {
 int used = 0 ;
 if ( STRPREFIX ( data , GREETING_PREFIX ) ) {
 const char * offset = strstr ( data , GREETING_POSTFIX ) ;
 if ( ! offset ) {


 }
 used = offset - data + strlen ( GREETING_POSTFIX ) ;




 char * start = NULL ;
 char * end = NULL ;
 char * skip ;
 if ( msg -> txLength > 0 ) {
 char * tmp ;
 if ( ( tmp = strchr ( msg -> txBuffer , '\r' ) ) ) {
 * tmp = '\0' ;
 }
 }
 skip = strstr ( data + used , msg -> txBuffer ) ;
 if ( skip ) {
 start = strstr ( skip + strlen ( msg -> txBuffer ) , LINE_ENDING ) ;
 }
 if ( start ) {
 char * passwd ;
 start += strlen ( LINE_ENDING ) ;
 passwd = strstr ( start , PASSWORD_PROMPT ) ;
 if ( passwd ) {


 int i ;
 if ( msg -> passwordHandler ( mon , msg , start , passwd - start + strlen ( PASSWORD_PROMPT ) , msg -> passwordOpaque ) < 0 ) return - 1 ;
 for ( i = 0 ;
 i < strlen ( PASSWORD_PROMPT ) ;
 i ++ ) start [ i ] = ' ' ;
 start = passwd ;
 }
 else {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "Password request seen, but no handler available" ) ) ;
 return - 1 ;
 }
 }
 end = strstr ( start , BASIC_PROMPT ) ;
 }
 if ( start && end ) {
 int want = end - start ;
 if ( want ) {
 if ( VIR_REALLOC_N ( msg -> rxBuffer , msg -> rxLength + want + 1 ) < 0 ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 memcpy ( msg -> rxBuffer + msg -> rxLength , start , want ) ;
 msg -> rxLength += want ;
 msg -> rxBuffer [ msg -> rxLength ] = '\0' ;

 }
 else {
 VIR_DEBUG ( "Finished 0 byte reply" ) ;

 PROBE ( QEMU_MONITOR_RECV_REPLY , "mon=%p reply=%s" , mon , msg -> rxBuffer ) ;
 msg -> finished = 1 ;
 used += end - ( data + used ) ;
 used += strlen ( BASIC_PROMPT ) ;
 }
 }


 }