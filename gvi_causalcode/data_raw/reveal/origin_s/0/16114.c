void uwsgi_php_set ( char * opt ) {
 uwsgi_sapi_module . ini_entries = realloc ( uwsgi_sapi_module . ini_entries , uphp . ini_size + strlen ( opt ) + 2 ) ;
 memcpy ( uwsgi_sapi_module . ini_entries + uphp . ini_size , opt , strlen ( opt ) ) ;
 uphp . ini_size += strlen ( opt ) + 1 ;
 uwsgi_sapi_module . ini_entries [ uphp . ini_size - 1 ] = '\n' ;
 uwsgi_sapi_module . ini_entries [ uphp . ini_size ] = 0 ;
 }