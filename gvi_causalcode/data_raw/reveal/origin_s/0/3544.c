static bool config_filter_match_local_name ( const struct config_filter * mask , const char * filter_local_name ) {
 const char * const * local_name = t_strsplit_spaces ( mask -> local_name , " " ) ;
 for ( ;
 * local_name != NULL ;
 local_name ++ ) {
 if ( dns_match_wildcard ( filter_local_name , * local_name ) == 0 ) return TRUE ;
 }
 return FALSE ;
 }