int qemuMonitorJSONSaveVirtualMemory ( qemuMonitorPtr mon , unsigned long long offset , size_t length , const char * path ) {
 return qemuMonitorJSONSaveMemory ( mon , "memsave" , offset , length , path ) ;
 }