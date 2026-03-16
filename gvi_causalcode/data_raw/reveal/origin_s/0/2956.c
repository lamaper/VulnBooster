TSReturnCode TSMgmtConfigIntSet ( const char * var_name , TSMgmtInt value ) {
 TSMgmtInt result ;
 char * buffer ;
 if ( TSMgmtIntGet ( var_name , & result ) != TS_SUCCESS ) {
 return TS_ERROR ;
 }
 int buffer_size = strlen ( var_name ) + 1 + 32 + 1 + 64 + 1 ;
 buffer = ( char * ) alloca ( buffer_size ) ;
 snprintf ( buffer , buffer_size , "%s %d %" PRId64 "" , var_name , MGMT_INT , value ) ;
 RecSignalManager ( MGMT_SIGNAL_PLUGIN_SET_CONFIG , buffer ) ;
 return TS_SUCCESS ;
 }