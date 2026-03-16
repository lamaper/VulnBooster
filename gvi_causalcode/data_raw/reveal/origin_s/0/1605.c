int qemuMonitorTextGetCPUInfo ( qemuMonitorPtr mon , int * * pids ) {
 char * qemucpus = NULL ;
 char * line ;
 int lastVcpu = - 1 ;
 pid_t * cpupids = NULL ;
 size_t ncpupids = 0 ;
 if ( qemuMonitorHMPCommand ( mon , "info cpus" , & qemucpus ) < 0 ) {
 qemuReportError ( VIR_ERR_INTERNAL_ERROR , "%s" , _ ( "cannot run monitor command to fetch CPU thread info" ) ) ;
 return - 1 ;
 }
 line = qemucpus ;
 do {
 char * offset = strchr ( line , '#' ) ;
 char * end = NULL ;
 int vcpu = 0 , tid = 0 ;
 if ( offset == NULL ) break ;
 if ( virStrToLong_i ( offset + 1 , & end , 10 , & vcpu ) < 0 ) goto error ;
 if ( end == NULL || * end != ':' ) goto error ;
 if ( ( offset = strstr ( line , "thread_id=" ) ) == NULL ) goto error ;
 if ( virStrToLong_i ( offset + strlen ( "thread_id=" ) , & end , 10 , & tid ) < 0 ) goto error ;
 if ( end == NULL || ! c_isspace ( * end ) ) goto error ;
 if ( vcpu != ( lastVcpu + 1 ) ) goto error ;
 if ( VIR_REALLOC_N ( cpupids , ncpupids + 1 ) < 0 ) goto error ;
 VIR_DEBUG ( "vcpu=%d pid=%d" , vcpu , tid ) ;
 cpupids [ ncpupids ++ ] = tid ;
 lastVcpu = vcpu ;
 line = strchr ( offset , '\r' ) ;
 if ( line == NULL ) line = strchr ( offset , '\n' ) ;
 }
 while ( line != NULL ) ;
 VIR_FREE ( qemucpus ) ;
 * pids = cpupids ;
 return ncpupids ;
 error : VIR_FREE ( qemucpus ) ;
 VIR_FREE ( cpupids ) ;
 return 0 ;
 }