void TSHttpHookAdd ( TSHttpHookID id , TSCont contp ) {
 INKContInternal * icontp ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_hook_id ( id ) == TS_SUCCESS ) ;
 icontp = reinterpret_cast < INKContInternal * > ( contp ) ;
 if ( id >= TS_SSL_FIRST_HOOK && id <= TS_SSL_LAST_HOOK ) {
 TSSslHookInternalID internalId = static_cast < TSSslHookInternalID > ( id - TS_SSL_FIRST_HOOK ) ;
 ssl_hooks -> append ( internalId , icontp ) ;
 }
 else {
 http_global_hooks -> append ( id , icontp ) ;
 }
 }