TSReturnCode TSMgmtSourceGet ( const char * var_name , TSMgmtSource * source ) {
 return REC_ERR_OKAY == RecGetRecordSource ( var_name , reinterpret_cast < RecSourceT * > ( source ) ) ? TS_SUCCESS : TS_ERROR ;
 }