static int config_filter_parser_cmp_rev ( struct config_filter_parser * const * p1 , struct config_filter_parser * const * p2 ) {
 return - config_filter_parser_cmp ( p1 , p2 ) ;
 }