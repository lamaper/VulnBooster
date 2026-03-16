static int qemuAgentIORead ( qemuAgentPtr mon ) {
 size_t avail = mon -> bufferLength - mon -> bufferOffset ;
 int ret = 0 ;
 if ( avail < 1024 ) {
 if ( mon -> bufferLength >= QEMU_AGENT_MAX_RESPONSE ) {
 virReportSystemError ( ERANGE , _ ( "No complete agent response found in %d bytes" ) , QEMU_AGENT_MAX_RESPONSE ) ;
 return - 1 ;
 }
 if ( VIR_REALLOC_N ( mon -> buffer , mon -> bufferLength + 1024 ) < 0 ) return - 1 ;
 mon -> bufferLength += 1024 ;
 avail += 1024 ;
 }
 while ( avail > 1 ) {
 int got ;
 got = read ( mon -> fd , mon -> buffer + mon -> bufferOffset , avail - 1 ) ;
 if ( got < 0 ) {
 if ( errno == EAGAIN ) break ;
 virReportSystemError ( errno , "%s" , _ ( "Unable to read from monitor" ) ) ;
 ret = - 1 ;
 break ;
 }
 if ( got == 0 ) break ;
 ret += got ;
 avail -= got ;
 mon -> bufferOffset += got ;
 mon -> buffer [ mon -> bufferOffset ] = '\0' ;
 }


 }