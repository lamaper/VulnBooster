void uwsgi_php_append_config ( char * filename ) {
 size_t file_size = 0 ;
 char * file_content = uwsgi_open_and_read ( filename , & file_size , 1 , NULL ) ;
 uwsgi_sapi_module . ini_entries = realloc ( uwsgi_sapi_module . ini_entries , uphp . ini_size + file_size ) ;
 memcpy ( uwsgi_sapi_module . ini_entries + uphp . ini_size , file_content , file_size ) ;
 uphp . ini_size += file_size - 1 ;
 free ( file_content ) ;
 }