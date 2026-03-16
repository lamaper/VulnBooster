struct config_filter_parser * const * config_filter_get_all ( struct config_filter_context * ctx ) {
 ARRAY_TYPE ( config_filter_parsers ) filters ;
 unsigned int i ;
 t_array_init ( & filters , 8 ) ;
 for ( i = 0 ;
 ctx -> parsers [ i ] != NULL ;
 i ++ ) {
 array_append ( & filters , & ctx -> parsers [ i ] , 1 ) ;
 }
 array_sort ( & filters , config_filter_parser_cmp_rev ) ;
 array_append_zero ( & filters ) ;
 return array_idx ( & filters , 0 ) ;
 }