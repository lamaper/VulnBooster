void TSStatIntIncrement ( int id , TSMgmtInt amount ) {
 sdk_assert ( sdk_sanity_check_stat_id ( id ) == TS_SUCCESS ) ;
 RecIncrRawStat ( api_rsb , nullptr , id , amount ) ;
 }