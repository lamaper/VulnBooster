int qemuMonitorTextSavePhysicalMemory ( qemuMonitorPtr mon , unsigned long long offset , size_t length , const char * path ) {
 return qemuMonitorTextSaveMemory ( mon , "pmemsave" , offset , length , path ) ;
 }