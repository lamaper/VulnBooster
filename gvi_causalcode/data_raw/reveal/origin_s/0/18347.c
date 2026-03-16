int config_filter_parsers_get ( struct config_filter_context * ctx , pool_t pool , const char * const * modules , const struct config_filter * filter , struct config_module_parser * * parsers_r , struct master_service_settings_output * output_r , const char * * error_r ) {
 struct config_filter_parser * const * src ;
 struct config_module_parser * dest ;
 const char * error = NULL , * * error_p ;
 unsigned int i , count ;
 src = config_filter_find_all ( ctx , pool , modules , filter , output_r ) ;
 for ( count = 0 ;
 src [ 0 ] -> parsers [ count ] . root != NULL ;
 count ++ ) ;
 dest = p_new ( pool , struct config_module_parser , count + 1 ) ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 dest [ i ] = src [ 0 ] -> parsers [ i ] ;
 dest [ i ] . parser = settings_parser_dup ( src [ 0 ] -> parsers [ i ] . parser , pool ) ;
 }
 for ( i = 1 ;
 src [ i ] != NULL ;
 i ++ ) {
 if ( config_filter_is_superset ( & src [ i ] -> filter , & src [ i - 1 ] -> filter ) ) error_p = NULL ;
 else error_p = & error ;
 if ( config_module_parser_apply_changes ( dest , src [ i ] , pool , error_p ) < 0 ) {
 i_assert ( error != NULL ) ;
 config_filter_parsers_free ( dest ) ;
 * error_r = error ;
 return - 1 ;
 }
 }
 * parsers_r = dest ;
 return 0 ;
 }