static int ts_lua_http_config_string_get ( lua_State * L ) {
 int conf ;
 const char * value ;
 int value_len ;
 ts_lua_http_ctx * http_ctx ;
 GET_HTTP_CONTEXT ( http_ctx , L ) ;
 conf = luaL_checkinteger ( L , 1 ) ;
 TSHttpTxnConfigStringGet ( http_ctx -> txnp , conf , & value , & value_len ) ;
 lua_pushlstring ( L , value , value_len ) ;
 return 1 ;
 }