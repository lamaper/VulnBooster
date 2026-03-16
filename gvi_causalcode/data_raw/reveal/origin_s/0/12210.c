void * TSHttpSsnSSLConnectionGet ( TSHttpSsn ssnp ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) ssnp ) == TS_SUCCESS ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 if ( cs == nullptr ) {
 return nullptr ;
 }
 SSLNetVConnection * ssl_vc = dynamic_cast < SSLNetVConnection * > ( cs -> get_netvc ( ) ) ;
 if ( ssl_vc == nullptr ) {
 return nullptr ;
 }
 return ( void * ) ssl_vc -> ssl ;
 }