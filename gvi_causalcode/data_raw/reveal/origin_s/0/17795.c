static int config_filter_parser_cmp ( struct config_filter_parser * const * p1 , struct config_filter_parser * const * p2 ) {
 const struct config_filter * f1 = & ( * p1 ) -> filter , * f2 = & ( * p2 ) -> filter ;
 if ( f1 -> local_name != NULL && f2 -> local_name == NULL ) return - 1 ;
 if ( f1 -> local_name == NULL && f2 -> local_name != NULL ) return 1 ;
 if ( f1 -> local_bits > f2 -> local_bits ) return - 1 ;
 if ( f1 -> local_bits < f2 -> local_bits ) return 1 ;
 if ( f1 -> remote_bits > f2 -> remote_bits ) return - 1 ;
 if ( f1 -> remote_bits < f2 -> remote_bits ) return 1 ;
 if ( f1 -> service != NULL && f2 -> service == NULL ) return - 1 ;
 if ( f1 -> service == NULL && f2 -> service != NULL ) return 1 ;
 return 0 ;
 }