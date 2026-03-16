static void ts_lua_inject_http_config_variables ( lua_State * L ) {
 size_t i ;
 for ( i = 0 ;
 i < sizeof ( ts_lua_http_config_vars ) / sizeof ( ts_lua_var_item ) ;
 i ++ ) {
 lua_pushinteger ( L , ts_lua_http_config_vars [ i ] . nvar ) ;
 lua_setglobal ( L , ts_lua_http_config_vars [ i ] . svar ) ;
 }
 for ( i = 0 ;
 i < sizeof ( ts_lua_http_timeout_vars ) / sizeof ( ts_lua_var_item ) ;
 i ++ ) {
 lua_pushinteger ( L , ts_lua_http_timeout_vars [ i ] . nvar ) ;
 lua_setglobal ( L , ts_lua_http_timeout_vars [ i ] . svar ) ;
 }
 }