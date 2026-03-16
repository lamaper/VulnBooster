int qemuMonitorTextSaveVirtualMemory ( qemuMonitorPtr mon , unsigned long long offset , size_t length , const char * path ) {
 return qemuMonitorTextSaveMemory ( mon , "memsave" , offset , length , path ) ;
 }