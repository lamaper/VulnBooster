bool config_filter_match ( const struct config_filter * mask , const struct config_filter * filter ) {
 if ( ! config_filter_match_service ( mask , filter ) ) return FALSE ;
 return config_filter_match_rest ( mask , filter ) ;
 }