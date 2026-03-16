static int ts_lua_http_config_string_set ( lua_State * L ) {
 int conf ;
 const char * value ;
 size_t value_len ;
 ts_lua_http_ctx * http_ctx ;
 GET_HTTP_CONTEXT ( http_ctx , L ) ;
 conf = luaL_checkinteger ( L , 1 ) ;
 value = luaL_checklstring ( L , 2 , & value_len ) ;
 TSHttpTxnConfigStringSet ( http_ctx -> txnp , conf , value , value_len ) ;
 return 0 ;
 }