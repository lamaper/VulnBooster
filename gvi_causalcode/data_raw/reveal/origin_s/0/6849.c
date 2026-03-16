static void cmd_server_connect ( const char * data ) {
 GHashTable * optlist ;
 char * addr ;
 void * free_arg ;
 if ( ! cmd_get_params ( data , & free_arg , 1 | PARAM_FLAG_OPTIONS , "connect" , & optlist , & addr ) ) return ;
 if ( * addr == '\0' || g_strcmp0 ( addr , "+" ) == 0 ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 if ( * addr == '+' ) window_create ( NULL , FALSE ) ;
 cmd_params_free ( free_arg ) ;
 }