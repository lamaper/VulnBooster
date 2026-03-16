static bool config_filter_is_superset ( const struct config_filter * sup , const struct config_filter * filter ) {
 if ( sup -> local_bits > filter -> local_bits ) return FALSE ;
 if ( sup -> remote_bits > filter -> remote_bits ) return FALSE ;
 if ( sup -> local_name != NULL && filter -> local_name == NULL ) {
 i_warning ( "%s" , sup -> local_name ) ;
 return FALSE ;
 }
 if ( sup -> service != NULL && filter -> service == NULL ) return FALSE ;
 return TRUE ;
 }