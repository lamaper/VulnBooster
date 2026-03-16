static virLogOutputPtr virLogNewOutputToFile ( virLogPriority priority , const char * file ) {
 int fd ;
 virLogOutputPtr ret = NULL ;
 fd = open ( file , O_CREAT | O_APPEND | O_WRONLY , S_IRUSR | S_IWUSR ) ;
 if ( fd < 0 ) {
 virReportSystemError ( errno , _ ( "failed to open %s" ) , file ) ;
 return NULL ;
 }
 if ( ! ( ret = virLogOutputNew ( virLogOutputToFd , virLogCloseFd , ( void * ) ( intptr_t ) fd , priority , VIR_LOG_TO_FILE , file ) ) ) {
 VIR_LOG_CLOSE ( fd ) ;
 return NULL ;
 }
 return ret ;
 }