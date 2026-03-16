static void qemuMonitorJSONHandleVNCConnect ( qemuMonitorPtr mon , virJSONValuePtr data ) {
 qemuMonitorJSONHandleVNC ( mon , data , VIR_DOMAIN_EVENT_GRAPHICS_CONNECT ) ;
 }