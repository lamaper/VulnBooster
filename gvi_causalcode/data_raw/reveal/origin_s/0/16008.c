int qemuMonitorJSONSavePhysicalMemory ( qemuMonitorPtr mon , unsigned long long offset , size_t length , const char * path ) {
 return qemuMonitorJSONSaveMemory ( mon , "pmemsave" , offset , length , path ) ;
 }