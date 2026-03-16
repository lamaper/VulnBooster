TSReturnCode TSHttpSsnClientProtocolStackGet ( TSHttpSsn ssnp , int n , const char * * result , int * actual ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 sdk_assert ( n == 0 || result != nullptr ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 int count = 0 ;
 if ( cs && n > 0 ) {
 auto mem = static_cast < ts : : StringView * > ( alloca ( sizeof ( ts : : StringView ) * n ) ) ;
 count = cs -> populate_protocol ( mem , n ) ;
 for ( int i = 0 ;
 i < count ;
 ++ i ) result [ i ] = mem [ i ] . ptr ( ) ;
 }
 if ( actual ) {
 * actual = count ;
 }
 return TS_SUCCESS ;
 }