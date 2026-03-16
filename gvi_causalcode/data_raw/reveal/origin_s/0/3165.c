static int php_uwsgi_startup ( sapi_module_struct * sapi_module ) {
 if ( php_module_startup ( & uwsgi_sapi_module , & uwsgi_module_entry , 1 ) == FAILURE ) {
 return FAILURE ;
 }
 else {
 return SUCCESS ;
 }
 }