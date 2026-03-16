qemuAgentPtr qemuAgentOpen ( virDomainObjPtr vm , const virDomainChrSourceDef * config , qemuAgentCallbacksPtr cb ) {
 qemuAgentPtr mon ;
 if ( ! cb || ! cb -> eofNotify ) {
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "EOF notify callback must be supplied" ) ) ;
 return NULL ;
 }
 if ( qemuAgentInitialize ( ) < 0 ) return NULL ;
 if ( ! ( mon = virObjectLockableNew ( qemuAgentClass ) ) ) return NULL ;
 mon -> fd = - 1 ;
 if ( virCondInit ( & mon -> notify ) < 0 ) {
 virReportSystemError ( errno , "%s" , _ ( "cannot initialize monitor condition" ) ) ;
 virObjectUnref ( mon ) ;
 return NULL ;
 }
 mon -> vm = vm ;
 mon -> cb = cb ;
 switch ( config -> type ) {
 case VIR_DOMAIN_CHR_TYPE_UNIX : mon -> fd = qemuAgentOpenUnix ( config -> data . nix . path , vm -> pid , & mon -> connectPending ) ;
 break ;
 case VIR_DOMAIN_CHR_TYPE_PTY : mon -> fd = qemuAgentOpenPty ( config -> data . file . path ) ;
 break ;
 default : virReportError ( VIR_ERR_INTERNAL_ERROR , _ ( "unable to handle monitor type: %s" ) , virDomainChrTypeToString ( config -> type ) ) ;
 goto cleanup ;
 }
 if ( mon -> fd == - 1 ) goto cleanup ;
 virObjectRef ( mon ) ;
 if ( ( mon -> watch = virEventAddHandle ( mon -> fd , VIR_EVENT_HANDLE_HANGUP | VIR_EVENT_HANDLE_ERROR | VIR_EVENT_HANDLE_READABLE | ( mon -> connectPending ? VIR_EVENT_HANDLE_WRITABLE : 0 ) , qemuAgentIO , mon , virObjectFreeCallback ) ) < 0 ) {
 virObjectUnref ( mon ) ;
 virReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "unable to register monitor events" ) ) ;
 goto cleanup ;
 }
 mon -> running = true ;
 VIR_DEBUG ( "New mon %p fd =%d watch=%d" , mon , mon -> fd , mon -> watch ) ;
 return mon ;
 cleanup : mon -> cb = NULL ;
 qemuAgentClose ( mon ) ;
 return NULL ;
 }