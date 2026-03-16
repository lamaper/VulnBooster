static int ts_lua_http_config_int_get ( lua_State * L ) {
 int conf ;
 int64_t value ;
 ts_lua_http_ctx * http_ctx ;
 GET_HTTP_CONTEXT ( http_ctx , L ) ;
 conf = luaL_checkinteger ( L , 1 ) ;
 TSHttpTxnConfigIntGet ( http_ctx -> txnp , conf , & value ) ;
 lua_pushnumber ( L , value ) ;
 return 1 ;
 }