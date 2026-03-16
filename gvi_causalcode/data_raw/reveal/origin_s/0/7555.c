TSReturnCode sdk_sanity_check_ssl_hook_id ( TSHttpHookID id ) {
 if ( id < TS_SSL_FIRST_HOOK || id > TS_SSL_LAST_HOOK ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }