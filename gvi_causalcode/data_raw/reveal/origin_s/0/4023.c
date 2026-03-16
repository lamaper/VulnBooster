static virLogOutputPtr virLogNewOutputToStderr ( virLogPriority priority ) {
 return virLogOutputNew ( virLogOutputToFd , NULL , ( void * ) STDERR_FILENO , priority , VIR_LOG_TO_STDERR , NULL ) ;
 }