int TSStatCreate ( const char * the_name , TSRecordDataType the_type , TSStatPersistence persist , TSStatSync sync ) {
 int id = ink_atomic_increment ( & api_rsb_index , 1 ) ;
 RecRawStatSyncCb syncer = RecRawStatSyncCount ;
 if ( ( sdk_sanity_check_null_ptr ( ( void * ) the_name ) != TS_SUCCESS ) || ( sdk_sanity_check_null_ptr ( ( void * ) api_rsb ) != TS_SUCCESS ) || ( id >= api_rsb -> max_stats ) ) {
 return TS_ERROR ;
 }
 switch ( sync ) {
 case TS_STAT_SYNC_SUM : syncer = RecRawStatSyncSum ;
 break ;
 case TS_STAT_SYNC_AVG : syncer = RecRawStatSyncAvg ;
 break ;
 case TS_STAT_SYNC_TIMEAVG : syncer = RecRawStatSyncHrTimeAvg ;
 break ;
 default : syncer = RecRawStatSyncCount ;
 break ;
 }
 switch ( persist ) {
 case TS_STAT_PERSISTENT : RecRegisterRawStat ( api_rsb , RECT_PLUGIN , the_name , ( RecDataT ) the_type , RECP_PERSISTENT , id , syncer ) ;
 break ;
 case TS_STAT_NON_PERSISTENT : RecRegisterRawStat ( api_rsb , RECT_PLUGIN , the_name , ( RecDataT ) the_type , RECP_NON_PERSISTENT , id , syncer ) ;
 break ;
 default : return TS_ERROR ;
 }
 return id ;
 }