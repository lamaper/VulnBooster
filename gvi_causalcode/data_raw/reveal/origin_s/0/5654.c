void TSHttpSsnDebugSet ( TSHttpSsn ssnp , int on ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 ( reinterpret_cast < ProxyClientSession * > ( ssnp ) ) -> debug_on = on ;
 }