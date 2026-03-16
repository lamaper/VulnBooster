int qemuMonitorTextCommandWithFd ( qemuMonitorPtr mon , const char * cmd , int scm_fd , char * * reply ) {
 return qemuMonitorTextCommandWithHandler ( mon , cmd , NULL , NULL , scm_fd , reply ) ;
 }