static void cmd_server_remove ( const char * data ) {
 SERVER_SETUP_REC * rec ;
 char * addr , * port , * chatnet ;
 void * free_arg ;
 if ( ! cmd_get_params ( data , & free_arg , 3 , & addr , & port , & chatnet ) ) return ;
 if ( * addr == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 if ( * port == '\0' ) {
 if ( * chatnet == '\0' ) rec = server_setup_find ( addr , - 1 , NULL ) ;
 else rec = server_setup_find ( addr , - 1 , chatnet ) ;
 }
 else {
 if ( * chatnet == '\0' ) rec = server_setup_find ( addr , atoi ( port ) , NULL ) ;
 else rec = server_setup_find ( addr , atoi ( port ) , chatnet ) ;
 }
 if ( rec == NULL ) printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_SETUPSERVER_NOT_FOUND , addr , port ) ;
 else {
 server_setup_remove ( rec ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_SETUPSERVER_REMOVED , addr , port ) ;
 }
 cmd_params_free ( free_arg ) ;
 }