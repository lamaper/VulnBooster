int TSHttpSsnTransactionCount ( TSHttpSsn ssnp ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 return cs -> get_transact_count ( ) ;
 }