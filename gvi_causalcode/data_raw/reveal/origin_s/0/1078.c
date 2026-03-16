void * TSHttpSsnArgGet ( TSHttpSsn ssnp , int arg_idx ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 sdk_assert ( arg_idx >= 0 && arg_idx < HTTP_SSN_TXN_MAX_USER_ARG ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 return cs -> get_user_arg ( arg_idx ) ;
 }