static int config_module_parser_apply_changes ( struct config_module_parser * dest , const struct config_filter_parser * src , pool_t pool , const char * * error_r ) {
 const char * conflict_key ;
 unsigned int i ;
 for ( i = 0 ;
 dest [ i ] . root != NULL ;
 i ++ ) {
 if ( settings_parser_apply_changes ( dest [ i ] . parser , src -> parsers [ i ] . parser , pool , error_r == NULL ? NULL : & conflict_key ) < 0 ) {
 i_assert ( error_r != NULL ) ;
 * error_r = t_strdup_printf ( "Conflict in setting %s " "found from filter at %s" , conflict_key , src -> file_and_line ) ;
 return - 1 ;
 }
 }
 return 0 ;
 }