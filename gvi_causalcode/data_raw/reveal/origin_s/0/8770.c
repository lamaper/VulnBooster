int uwsgi_php_init ( void ) {
 struct uwsgi_string_list * pset = uphp . set ;
 struct uwsgi_string_list * append_config = uphp . append_config ;


 while ( append_config ) {
 uwsgi_php_append_config ( append_config -> value ) ;
 append_config = append_config -> next ;
 }
 while ( pset ) {
 uwsgi_php_set ( pset -> value ) ;
 pset = pset -> next ;
 }
 if ( uphp . dump_config ) {
 uwsgi_log ( "--- PHP custom config ---\n\n" ) ;
 uwsgi_log ( "%s\n" , uwsgi_sapi_module . ini_entries ) ;
 uwsgi_log ( "--- end of PHP custom config ---\n" ) ;
 }
 if ( uphp . docroot ) {
 char * orig_docroot = uphp . docroot ;
 uphp . docroot = uwsgi_expand_path ( uphp . docroot , strlen ( uphp . docroot ) , NULL ) ;
 if ( ! uphp . docroot ) {
 uwsgi_log ( "unable to set php docroot to %s\n" , orig_docroot ) ;
 exit ( 1 ) ;
 }
 uwsgi_log ( "PHP document root set to %s\n" , uphp . docroot ) ;
 uphp . docroot_len = strlen ( uphp . docroot ) ;
 }
 if ( uphp . sapi_name ) {
 uwsgi_sapi_module . name = uphp . sapi_name ;
 }
 uwsgi_sapi_module . startup ( & uwsgi_sapi_module ) ;
 uwsgi_log ( "PHP %s initialized\n" , PHP_VERSION ) ;
 return 0 ;
 }