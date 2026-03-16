TSReturnCode TSMgmtIntCreate ( TSRecordType rec_type , const char * name , TSMgmtInt data_default , TSRecordUpdateType update_type , TSRecordCheckType check_type , const char * check_regex , TSRecordAccessType access_type ) {
 if ( check_regex == nullptr && check_type != TS_RECORDCHECK_NULL ) {
 return TS_ERROR ;
 }
 if ( REC_ERR_OKAY != RecRegisterConfigInt ( ( enum RecT ) rec_type , name , ( RecInt ) data_default , ( enum RecUpdateT ) update_type , ( enum RecCheckT ) check_type , check_regex , REC_SOURCE_PLUGIN , ( enum RecAccessT ) access_type ) ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }