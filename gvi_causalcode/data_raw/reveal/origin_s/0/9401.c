static void qemuAgentUpdateWatch ( qemuAgentPtr mon ) {
 int events = VIR_EVENT_HANDLE_HANGUP | VIR_EVENT_HANDLE_ERROR ;
 if ( mon -> lastError . code == VIR_ERR_OK ) {
 events |= VIR_EVENT_HANDLE_READABLE ;
 if ( mon -> msg && mon -> msg -> txOffset < mon -> msg -> txLength ) events |= VIR_EVENT_HANDLE_WRITABLE ;
 }
 virEventUpdateHandle ( mon -> watch , events ) ;
 }