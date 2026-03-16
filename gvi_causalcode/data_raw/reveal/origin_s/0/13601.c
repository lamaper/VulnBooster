void config_filter_deinit ( struct config_filter_context * * _ctx ) {
 struct config_filter_context * ctx = * _ctx ;
 unsigned int i ;
 * _ctx = NULL ;
 for ( i = 0 ;
 ctx -> parsers [ i ] != NULL ;
 i ++ ) config_filter_parsers_free ( ctx -> parsers [ i ] -> parsers ) ;
 pool_unref ( & ctx -> pool ) ;
 }