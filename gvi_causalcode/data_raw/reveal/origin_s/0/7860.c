static int qemuMonitorJSONCommand ( qemuMonitorPtr mon , virJSONValuePtr cmd , virJSONValuePtr * reply ) {
 return qemuMonitorJSONCommandWithFd ( mon , cmd , - 1 , reply ) ;
 }