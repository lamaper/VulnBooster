static int map_uri_to_page_cache_file ( ngx_http_request_t * r , ngx_str_t * public_dir , const u_char * filename , size_t filename_len , ngx_str_t * page_cache_file ) {
 u_char * end ;
 if ( ( r -> method != NGX_HTTP_GET && r -> method != NGX_HTTP_HEAD ) || filename_len == 0 ) {
 return 0 ;
 }
 if ( mapped_filename_equals ( filename , filename_len , public_dir ) ) {
 if ( filename_len + sizeof ( "/index.html" ) > page_cache_file -> len ) {
 return 0 ;
 }
 end = ngx_copy ( page_cache_file -> data , filename , filename_len ) ;
 if ( filename [ filename_len - 1 ] != '/' ) {
 end = ngx_copy ( end , "/" , 1 ) ;
 }
 end = ngx_copy ( end , "index.html" , sizeof ( "index.html" ) ) ;
 }
 else {
 if ( filename_len + sizeof ( ".html" ) > page_cache_file -> len ) {
 return 0 ;
 }
 end = ngx_copy ( page_cache_file -> data , filename , filename_len ) ;
 end = ngx_copy ( end , ".html" , sizeof ( ".html" ) ) ;
 }
 if ( file_exists ( page_cache_file -> data , 0 ) ) {
 page_cache_file -> len = end - page_cache_file -> data - 1 ;
 return 1 ;
 }
 else {
 return 0 ;
 }
 }