TSReturnCode TSTextLogObjectCreate ( const char * filename , int mode , TSTextLogObject * new_object ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) filename ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) new_object ) == TS_SUCCESS ) ;
 if ( mode < 0 || mode >= TS_LOG_MODE_INVALID_FLAG ) {
 * new_object = nullptr ;
 return TS_ERROR ;
 }
 TextLogObject * tlog = new TextLogObject ( filename , Log : : config -> logfile_dir , ( bool ) mode & TS_LOG_MODE_ADD_TIMESTAMP , nullptr , Log : : config -> rolling_enabled , Log : : config -> collation_preproc_threads , Log : : config -> rolling_interval_sec , Log : : config -> rolling_offset_hr , Log : : config -> rolling_size_mb ) ;
 if ( tlog == nullptr ) {
 * new_object = nullptr ;
 return TS_ERROR ;
 }
 int err = ( mode & TS_LOG_MODE_DO_NOT_RENAME ? Log : : config -> log_object_manager . manage_api_object ( tlog , 0 ) : Log : : config -> log_object_manager . manage_api_object ( tlog ) ) ;
 if ( err != LogObjectManager : : NO_FILENAME_CONFLICTS ) {
 delete tlog ;
 * new_object = nullptr ;
 return TS_ERROR ;
 }
 * new_object = ( TSTextLogObject ) tlog ;
 return TS_SUCCESS ;
 }