static void qemuMonitorJSONHandleVNCDisconnect ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 qemuMonitorJSONHandleVNC ( mon , data , VIR_DOMAIN_EVENT_GRAPHICS_DISCONNECT ) ;
 }