TSReturnCode TSMgmtCounterGet ( const char * var_name , TSMgmtCounter * result ) {
 return RecGetRecordCounter ( ( char * ) var_name , ( RecCounter * ) result ) == REC_ERR_OKAY ? TS_SUCCESS : TS_ERROR ;
 }