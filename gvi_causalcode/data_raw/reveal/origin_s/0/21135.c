static int ts_lua_http_config_int_set ( lua_State * L ) {
 int conf ;
 int value ;
 ts_lua_http_ctx * http_ctx ;
 GET_HTTP_CONTEXT ( http_ctx , L ) ;
 conf = luaL_checkinteger ( L , 1 ) ;
 value = luaL_checkinteger ( L , 2 ) ;
 TSHttpTxnConfigIntSet ( http_ctx -> txnp , conf , value ) ;
 return 0 ;
 }