TSReturnCode TSHttpSsnClientFdGet ( TSHttpSsn ssnp , int * fdp ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) fdp ) == TS_SUCCESS ) ;
 VConnection * basecs = reinterpret_cast < VConnection * > ( ssnp ) ;
 ProxyClientSession * cs = dynamic_cast < ProxyClientSession * > ( basecs ) ;
 if ( cs == nullptr ) {
 return TS_ERROR ;
 }
 NetVConnection * vc = cs -> get_netvc ( ) ;
 if ( vc == nullptr ) {
 return TS_ERROR ;
 }
 * fdp = vc -> get_socket ( ) ;
 return TS_SUCCESS ;
 }