time_t time_to_time_t ( VALUE time ) {
 return ( time_t ) NUM2TIMET ( rb_Integer ( time ) ) ;
 }