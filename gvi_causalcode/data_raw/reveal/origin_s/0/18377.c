static int mapped_filename_equals ( const u_char * filename , size_t filename_len , ngx_str_t * str ) {
 return ( str -> len == filename_len && memcmp ( str -> data , filename , filename_len ) == 0 ) || ( str -> len == filename_len - 1 && filename [ filename_len - 1 ] == '/' && memcmp ( str -> data , filename , filename_len - 1 ) == 0 ) ;
 }