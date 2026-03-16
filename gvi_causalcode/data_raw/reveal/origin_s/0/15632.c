int qemuMonitorJSONIOProcess ( qemuMonitorPtr mon , const char * data , size_t len , qemuMonitorMessagePtr msg ) {
 int used = 0 ;
 while ( used < len ) {
 char * nl = strstr ( data + used , LINE_ENDING ) ;
 if ( nl ) {
 int got = nl - ( data + used ) ;
 char * line = strndup ( data + used , got ) ;
 if ( ! line ) {
 virReportOOMError ( ) ;
 return - 1 ;
 }
 used += got + strlen ( LINE_ENDING ) ;
 line [ got ] = '\0' ;
 if ( qemuMonitorJSONIOProcessLine ( mon , line , msg ) < 0 ) {
 VIR_FREE ( line ) ;
 return - 1 ;
 }
 VIR_FREE ( line ) ;
 }
 else {
 break ;
 }
 }
 VIR_DEBUG ( "Total used %d bytes out of %zd available in buffer" , used , len ) ;
 return used ;
 }