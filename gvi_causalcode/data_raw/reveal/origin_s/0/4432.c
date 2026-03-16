void uwsgi_opt_php_ini ( char * opt , char * value , void * foobar ) {
 uwsgi_sapi_module . php_ini_path_override = uwsgi_str ( value ) ;
 uwsgi_sapi_module . php_ini_ignore = 1 ;
 }