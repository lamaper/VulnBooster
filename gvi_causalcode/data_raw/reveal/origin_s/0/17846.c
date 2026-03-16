static int rfc2231_parameter_cmp ( const struct rfc2231_parameter * r1 , const struct rfc2231_parameter * r2 ) {
 int ret ;
 ret = strcmp ( r1 -> key , r2 -> key ) ;
 if ( ret != 0 ) return ret ;
 return r1 -> idx < r2 -> idx ? - 1 : ( r1 -> idx > r2 -> idx ? 1 : 0 ) ;
 }