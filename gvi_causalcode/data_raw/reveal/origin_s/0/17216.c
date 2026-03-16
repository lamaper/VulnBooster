TSReturnCode TSMgmtStringGet ( const char * var_name , TSMgmtString * result ) {
 RecString tmp = nullptr ;
 ( void ) RecGetRecordString_Xmalloc ( ( char * ) var_name , & tmp ) ;
 if ( tmp ) {
 * result = tmp ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }