void stop_postmaster ( bool fast ) {
 ClusterInfo * cluster ;
 if ( os_info . running_cluster == & old_cluster ) cluster = & old_cluster ;
 else if ( os_info . running_cluster == & new_cluster ) cluster = & new_cluster ;
 else return ;
 exec_prog ( SERVER_STOP_LOG_FILE , NULL , ! fast , "\"%s/pg_ctl\" -w -D \"%s\" -o \"%s\" %s stop" , cluster -> bindir , cluster -> pgconfig , cluster -> pgopts ? cluster -> pgopts : "" , fast ? "-m fast" : "" ) ;
 os_info . running_cluster = NULL ;
 }