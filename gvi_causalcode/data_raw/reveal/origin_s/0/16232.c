PHP_MINIT_FUNCTION ( uwsgi_php_minit ) {
 php_session_register_module ( & ps_mod_uwsgi ) ;
 struct uwsgi_string_list * usl = uphp . constants ;
 while ( usl ) {
 char * equal = strchr ( usl -> value , '=' ) ;
 if ( equal ) {
 size_t name_len = equal - usl -> value ;
 char * name = usl -> value ;
 char * strval = equal + 1 ;
 equal = NULL ;


 }
 usl = usl -> next ;
 }
 return SUCCESS ;
 }