struct config_filter_context * config_filter_init ( pool_t pool ) {
 struct config_filter_context * ctx ;
 ctx = p_new ( pool , struct config_filter_context , 1 ) ;
 ctx -> pool = pool ;
 return ctx ;
 }