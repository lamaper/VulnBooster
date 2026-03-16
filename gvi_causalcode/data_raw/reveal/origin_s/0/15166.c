static int qemuAgentIOProcessData ( qemuAgentPtr mon , char * data , size_t len , qemuAgentMessagePtr msg ) {
 int used = 0 ;
 size_t i = 0 ;

 VIR_ERROR ( "[%s]" , str1 ) ;
 VIR_FREE ( str1 ) ;


 char * nl = strstr ( data + used , LINE_ENDING ) ;
 if ( nl ) {
 int got = nl - ( data + used ) ;
 for ( i = 0 ;
 i < strlen ( LINE_ENDING ) ;
 i ++ ) data [ used + got + i ] = '\0' ;
 if ( qemuAgentIOProcessLine ( mon , data + used , msg ) < 0 ) return - 1 ;
 used += got + strlen ( LINE_ENDING ) ;
 }
 else {
 break ;
 }
 }
 VIR_DEBUG ( "Total used %d bytes out of %zd available in buffer" , used , len ) ;
 return used ;
 }