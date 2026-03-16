TSReturnCode TSMgmtFloatGet ( const char * var_name , TSMgmtFloat * result ) {
 return RecGetRecordFloat ( ( char * ) var_name , ( RecFloat * ) result ) == REC_ERR_OKAY ? TS_SUCCESS : TS_ERROR ;
 }