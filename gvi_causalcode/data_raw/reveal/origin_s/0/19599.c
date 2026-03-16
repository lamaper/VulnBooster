void TSStatIntSet ( int id , TSMgmtInt value ) {
 sdk_assert ( sdk_sanity_check_stat_id ( id ) == TS_SUCCESS ) ;
 RecSetGlobalRawStatSum ( api_rsb , id , value ) ;
 }