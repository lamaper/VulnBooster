int qemuMonitorJSONMigrate ( qemuMonitorPtr mon , unsigned int flags , const char * uri ) {
 int ret ;
 virJSONValuePtr cmd = qemuMonitorJSONMakeCommand ( "migrate" , "b:detach" , flags & QEMU_MONITOR_MIGRATE_BACKGROUND ? 1 : 0 , "b:blk" , flags & QEMU_MONITOR_MIGRATE_NON_SHARED_DISK ? 1 : 0 , "b:inc" , flags & QEMU_MONITOR_MIGRATE_NON_SHARED_INC ? 1 : 0 , "s:uri" , uri , NULL ) ;
 virJSONValuePtr reply = NULL ;
 if ( ! cmd ) return - 1 ;
 ret = qemuMonitorJSONCommand ( mon , cmd , & reply ) ;
 if ( ret == 0 ) ret = qemuMonitorJSONCheckError ( cmd , reply ) ;
 virJSONValueFree ( cmd ) ;
 virJSONValueFree ( reply ) ;
 return ret ;
 }