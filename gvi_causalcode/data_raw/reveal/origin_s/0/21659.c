static int qemuAgentIOWrite ( qemuAgentPtr mon ) {
 int done ;
 if ( ! mon -> msg || mon -> msg -> txOffset == mon -> msg -> txLength ) return 0 ;
 done = safewrite ( mon -> fd , mon -> msg -> txBuffer + mon -> msg -> txOffset , mon -> msg -> txLength - mon -> msg -> txOffset ) ;
 if ( done < 0 ) {
 if ( errno == EAGAIN ) return 0 ;
 virReportSystemError ( errno , "%s" , _ ( "Unable to write to monitor" ) ) ;
 return - 1 ;
 }
 mon -> msg -> txOffset += done ;
 return done ;
 }