TSReturnCode TSMgmtIntGet ( const char * var_name , TSMgmtInt * result ) {
 return RecGetRecordInt ( ( char * ) var_name , ( RecInt * ) result ) == REC_ERR_OKAY ? TS_SUCCESS : TS_ERROR ;
 }