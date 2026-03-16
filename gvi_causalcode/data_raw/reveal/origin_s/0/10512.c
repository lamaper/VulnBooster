int rfc2231_parse ( struct rfc822_parser_context * ctx , const char * const * * result_r ) {
 ARRAY_TYPE ( const_string ) result ;
 ARRAY ( struct rfc2231_parameter ) rfc2231_params_arr ;
 struct rfc2231_parameter rfc2231_param ;
 const struct rfc2231_parameter * rfc2231_params ;
 const char * key , * value , * p , * p2 ;
 string_t * str ;
 unsigned int i , j , count , next , next_idx ;
 bool ok , have_extended , broken = FALSE ;
 int ret ;
 i_zero ( & rfc2231_param ) ;
 t_array_init ( & result , 8 ) ;
 t_array_init ( & rfc2231_params_arr , 8 ) ;
 while ( ( ret = rfc822_parse_content_param ( ctx , & key , & value ) ) != 0 ) {
 if ( ret < 0 ) {
 broken = TRUE ;
 if ( ctx -> data >= ctx -> end ) break ;
 ctx -> data ++ ;
 continue ;
 }
 p = strchr ( key , '*' ) ;
 if ( p != NULL ) {
 p2 = p ;
 if ( p [ 1 ] != '\0' ) {
 p ++ ;
 rfc2231_param . idx = 0 ;
 for ( ;
 * p >= '0' && * p <= '9' ;
 p ++ ) {
 rfc2231_param . idx = rfc2231_param . idx * 10 + * p - '0' ;
 }
 }
 if ( * p != '*' ) rfc2231_param . extended = FALSE ;
 else {
 rfc2231_param . extended = TRUE ;
 p ++ ;
 }
 if ( * p != '\0' ) p = NULL ;
 else {
 rfc2231_param . key = t_strdup_until ( key , p2 ) ;
 rfc2231_param . value = value ;
 array_append ( & rfc2231_params_arr , & rfc2231_param , 1 ) ;
 }
 }
 if ( p == NULL ) {
 array_append ( & result , & key , 1 ) ;
 array_append ( & result , & value , 1 ) ;
 }
 }
 if ( array_count ( & rfc2231_params_arr ) == 0 ) {
 array_append_zero ( & result ) ;
 * result_r = array_idx ( & result , 0 ) ;
 return broken ? - 1 : 0 ;
 }
 array_sort ( & rfc2231_params_arr , rfc2231_parameter_cmp ) ;
 rfc2231_params = array_get ( & rfc2231_params_arr , & count ) ;
 str = t_str_new ( 64 ) ;
 for ( i = 0 ;
 i < count ;
 i = next ) {
 ok = TRUE ;
 have_extended = FALSE ;
 next_idx = 0 ;
 for ( j = i ;
 j < count ;
 j ++ ) {
 if ( strcasecmp ( rfc2231_params [ i ] . key , rfc2231_params [ j ] . key ) != 0 ) break ;
 if ( rfc2231_params [ j ] . idx != next_idx ) {
 ok = FALSE ;
 }
 if ( rfc2231_params [ j ] . extended ) have_extended = TRUE ;
 next_idx ++ ;
 }
 next = j ;
 if ( ! ok ) {
 for ( j = i ;
 j < next ;
 j ++ ) {
 key = t_strdup_printf ( rfc2231_params [ j ] . extended ? "%s*%u*" : "%s*%u" , rfc2231_params [ j ] . key , rfc2231_params [ j ] . idx ) ;
 array_append ( & result , & key , 1 ) ;
 array_append ( & result , & rfc2231_params [ j ] . value , 1 ) ;
 }
 }
 else {
 str_truncate ( str , 0 ) ;
 if ( ! rfc2231_params [ i ] . extended && have_extended ) str_append ( str , "''" ) ;
 for ( j = i ;
 j < next ;
 j ++ ) {
 if ( ! rfc2231_params [ j ] . extended && have_extended ) {
 rfc2231_escape ( str , rfc2231_params [ j ] . value ) ;
 }
 else {
 str_append ( str , rfc2231_params [ j ] . value ) ;
 }
 }
 key = rfc2231_params [ i ] . key ;
 if ( have_extended ) key = t_strconcat ( key , "*" , NULL ) ;
 value = t_strdup ( str_c ( str ) ) ;
 array_append ( & result , & key , 1 ) ;
 array_append ( & result , & value , 1 ) ;
 }
 }
 array_append_zero ( & result ) ;
 * result_r = array_idx ( & result , 0 ) ;
 return broken ? - 1 : 0 ;
 }