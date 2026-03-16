bool config_filters_equal ( const struct config_filter * f1 , const struct config_filter * f2 ) {
 if ( null_strcmp ( f1 -> service , f2 -> service ) != 0 ) return FALSE ;
 if ( f1 -> remote_bits != f2 -> remote_bits ) return FALSE ;
 if ( ! net_ip_compare ( & f1 -> remote_net , & f2 -> remote_net ) ) return FALSE ;
 if ( f1 -> local_bits != f2 -> local_bits ) return FALSE ;
 if ( ! net_ip_compare ( & f1 -> local_net , & f2 -> local_net ) ) return FALSE ;
 if ( null_strcasecmp ( f1 -> local_name , f2 -> local_name ) != 0 ) return FALSE ;
 return TRUE ;
 }