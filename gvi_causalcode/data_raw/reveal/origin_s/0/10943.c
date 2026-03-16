static void cmd_channel_remove ( const char * data ) {
 CHANNEL_SETUP_REC * rec ;
 char * chatnet , * channel ;
 void * free_arg ;
 if ( ! cmd_get_params ( data , & free_arg , 2 , & channel , & chatnet ) ) return ;
 if ( * chatnet == '\0' || * channel == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 rec = channel_setup_find ( channel , chatnet ) ;
 if ( rec == NULL ) printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CHANSETUP_NOT_FOUND , channel , chatnet ) ;
 else {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CHANSETUP_REMOVED , channel , chatnet ) ;
 channel_setup_remove ( rec ) ;
 }
 cmd_params_free ( free_arg ) ;
 }