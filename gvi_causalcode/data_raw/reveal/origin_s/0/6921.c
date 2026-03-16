int TSHttpSsnDebugGet ( TSHttpSsn ssnp ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 return ( reinterpret_cast < ProxyClientSession * > ( ssnp ) ) -> debug ( ) ;
 }