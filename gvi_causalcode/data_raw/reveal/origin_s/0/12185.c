static int find_base_uri ( ngx_http_request_t * r , const passenger_loc_conf_t * loc , ngx_str_t * found_base_uri ) {
 ngx_uint_t i ;
 ngx_str_t * base_uris , * base_uri , * uri ;
 if ( loc -> base_uris == NGX_CONF_UNSET_PTR ) {
 return 0 ;
 }
 else {
 base_uris = ( ngx_str_t * ) loc -> base_uris -> elts ;
 uri = & r -> uri ;
 for ( i = 0 ;
 i < loc -> base_uris -> nelts ;
 i ++ ) {
 base_uri = & base_uris [ i ] ;
 if ( base_uri -> len == 1 && base_uri -> data [ 0 ] == '/' ) {
 continue ;
 }
 if ( ( uri -> len == base_uri -> len && ngx_strncmp ( uri -> data , base_uri -> data , uri -> len ) == 0 ) || ( uri -> len > base_uri -> len && ngx_strncmp ( uri -> data , base_uri -> data , base_uri -> len ) == 0 && uri -> data [ base_uri -> len ] == ( u_char ) '/' ) ) {
 * found_base_uri = * base_uri ;
 return 1 ;
 }
 }
 return 0 ;
 }
 }