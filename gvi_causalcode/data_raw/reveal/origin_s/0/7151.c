static int qemuAgentIOProcess ( qemuAgentPtr mon ) {
 int len ;
 qemuAgentMessagePtr msg = NULL ;
 if ( mon -> msg && mon -> msg -> txOffset == mon -> msg -> txLength ) msg = mon -> msg ;

 char * str2 = qemuAgentEscapeNonPrintable ( mon -> buffer ) ;
 VIR_ERROR ( _ ( "Process %zu %p %p [[[%s]]][[[%s]]]" ) , mon -> bufferOffset , mon -> msg , msg , str1 , str2 ) ;
 VIR_FREE ( str1 ) ;
 VIR_FREE ( str2 ) ;


 if ( len < 0 ) return - 1 ;
 if ( len < mon -> bufferOffset ) {
 memmove ( mon -> buffer , mon -> buffer + len , mon -> bufferOffset - len ) ;
 mon -> bufferOffset -= len ;
 }
 else {
 VIR_FREE ( mon -> buffer ) ;
 mon -> bufferOffset = mon -> bufferLength = 0 ;
 }


 return len ;
 }