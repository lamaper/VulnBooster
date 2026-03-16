void TSHttpSsnHookAdd ( TSHttpSsn ssnp , TSHttpHookID id , TSCont contp ) {
 sdk_assert ( sdk_sanity_check_http_ssn ( ssnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_hook_id ( id ) == TS_SUCCESS ) ;
 ProxyClientSession * cs = reinterpret_cast < ProxyClientSession * > ( ssnp ) ;
 cs -> ssn_hook_append ( id , ( INKContInternal * ) contp ) ;
 }