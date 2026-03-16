static bool config_filter_match_rest ( const struct config_filter * mask , const struct config_filter * filter ) {
 bool matched ;
 if ( mask -> local_name != NULL ) {
 if ( filter -> local_name == NULL ) return FALSE ;
 T_BEGIN {
 matched = config_filter_match_local_name ( mask , filter -> local_name ) ;
 }
 T_END ;
 if ( ! matched ) return FALSE ;
 }
 if ( mask -> remote_bits != 0 ) {
 if ( filter -> remote_bits == 0 ) return FALSE ;
 if ( ! net_is_in_network ( & filter -> remote_net , & mask -> remote_net , mask -> remote_bits ) ) return FALSE ;
 }
 if ( mask -> local_bits != 0 ) {
 if ( filter -> local_bits == 0 ) return FALSE ;
 if ( ! net_is_in_network ( & filter -> local_net , & mask -> local_net , mask -> local_bits ) ) return FALSE ;
 }
 return TRUE ;
 }