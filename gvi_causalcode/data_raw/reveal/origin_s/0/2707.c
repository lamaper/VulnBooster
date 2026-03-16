static int ts_lua_http_timeout_set ( lua_State * L ) {
 int conf ;
 int value ;
 ts_lua_http_ctx * http_ctx ;
 GET_HTTP_CONTEXT ( http_ctx , L ) ;
 conf = luaL_checkinteger ( L , 1 ) ;
 value = luaL_checkinteger ( L , 2 ) ;
 switch ( conf ) {
 case TS_LUA_TIMEOUT_ACTIVE : TSDebug ( TS_LUA_DEBUG_TAG , "setting active timeout" ) ;
 TSHttpTxnActiveTimeoutSet ( http_ctx -> txnp , value ) ;
 break ;
 case TS_LUA_TIMEOUT_CONNECT : TSDebug ( TS_LUA_DEBUG_TAG , "setting connect timeout" ) ;
 TSHttpTxnConnectTimeoutSet ( http_ctx -> txnp , value ) ;
 break ;
 case TS_LUA_TIMEOUT_DNS : TSDebug ( TS_LUA_DEBUG_TAG , "setting dns timeout" ) ;
 TSHttpTxnDNSTimeoutSet ( http_ctx -> txnp , value ) ;
 break ;
 case TS_LUA_TIMEOUT_NO_ACTIVITY : TSDebug ( TS_LUA_DEBUG_TAG , "setting no activity timeout" ) ;
 TSHttpTxnNoActivityTimeoutSet ( http_ctx -> txnp , value ) ;
 break ;
 default : TSError ( "[ts_lua] Unsupported timeout config option for lua plugin" ) ;
 break ;
 }
 return 0 ;
 }