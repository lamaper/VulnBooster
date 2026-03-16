TSReturnCode sdk_sanity_check_http_parser ( TSHttpParser parser ) {
 if ( parser == nullptr ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }