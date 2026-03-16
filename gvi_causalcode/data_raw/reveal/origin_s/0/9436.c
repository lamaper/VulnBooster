void config_filter_parsers_free ( struct config_module_parser * parsers ) {
 unsigned int i ;
 for ( i = 0 ;
 parsers [ i ] . root != NULL ;
 i ++ ) settings_parser_deinit ( & parsers [ i ] . parser ) ;
 }