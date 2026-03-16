int uwsgi_php_walk ( struct wsgi_request * wsgi_req , char * full_path , char * docroot , size_t docroot_len , char * * path_info ) {
 uint16_t i ;
 char * ptr = wsgi_req -> path_info ;
 char * dst = full_path + docroot_len ;
 char * part = ptr ;
 int part_size = 0 ;
 struct stat st ;
 if ( wsgi_req -> path_info_len == 0 ) return 0 ;
 if ( ptr [ 0 ] == '/' ) part_size ++ ;
 for ( i = 0 ;
 i < wsgi_req -> path_info_len ;
 i ++ ) {
 if ( ptr [ i ] == '/' ) {
 memcpy ( dst , part , part_size - 1 ) ;
 * ( dst + part_size - 1 ) = 0 ;
 if ( stat ( full_path , & st ) ) {
 return - 1 ;
 }
 if ( ! S_ISDIR ( st . st_mode ) ) {
 if ( i < ( wsgi_req -> path_info_len ) - 1 ) {
 * path_info = ptr + i ;
 }
 return 0 ;
 }
 * ( dst + part_size - 1 ) = '/' ;
 * ( dst + part_size ) = 0 ;
 dst += part_size ;
 part_size = 0 ;
 part = ptr + i + 1 ;
 }
 part_size ++ ;
 }
 if ( part < wsgi_req -> path_info + wsgi_req -> path_info_len ) {
 memcpy ( dst , part , part_size - 1 ) ;
 * ( dst + part_size - 1 ) = 0 ;
 if ( stat ( full_path , & st ) ) {
 return - 1 ;
 }
 }
 return 0 ;
 }