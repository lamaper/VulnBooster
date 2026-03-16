static struct config_filter_parser * const * config_filter_find_all ( struct config_filter_context * ctx , pool_t pool , const char * const * modules , const struct config_filter * filter , struct master_service_settings_output * output_r ) {
 ARRAY_TYPE ( config_filter_parsers ) matches ;
 ARRAY_TYPE ( const_string ) service_names ;
 unsigned int i ;
 i_zero ( output_r ) ;
 p_array_init ( & matches , pool , 8 ) ;
 p_array_init ( & service_names , pool , 8 ) ;
 for ( i = 0 ;
 ctx -> parsers [ i ] != NULL ;
 i ++ ) {
 const struct config_filter * mask = & ctx -> parsers [ i ] -> filter ;
 if ( ! config_filter_match_service ( mask , filter ) ) {
 if ( ! str_array_contains ( & service_names , mask -> service ) && have_changed_settings ( ctx -> parsers [ i ] , modules ) ) array_append ( & service_names , & mask -> service , 1 ) ;
 continue ;
 }
 if ( mask -> local_bits > 0 || mask -> local_name != NULL ) output_r -> service_uses_local = TRUE ;
 if ( mask -> remote_bits > 0 ) output_r -> service_uses_remote = TRUE ;
 if ( config_filter_match_rest ( mask , filter ) ) {
 if ( mask -> local_bits > 0 || mask -> local_name != NULL ) output_r -> used_local = TRUE ;
 if ( mask -> remote_bits > 0 ) output_r -> used_remote = TRUE ;
 array_append ( & matches , & ctx -> parsers [ i ] , 1 ) ;
 }
 }
 if ( filter -> service == NULL ) {
 array_append_zero ( & service_names ) ;
 output_r -> specific_services = array_idx ( & service_names , 0 ) ;
 }
 array_sort ( & matches , config_filter_parser_cmp ) ;
 array_append_zero ( & matches ) ;
 return array_idx ( & matches , 0 ) ;
 }