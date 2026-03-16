const char * TSHttpSsnClientProtocolStackContains ( TSHttpSsn ssnp , const char * tag ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 return cs -> protocol_contains ( ts : : StringView ( tag ) ) ;
 }