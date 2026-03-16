static TSReturnCode sdk_sanity_check_stat_id ( int id ) {
 if ( id < 0 || id >= api_rsb -> max_stats ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }