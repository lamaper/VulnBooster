static void cmd_channel_add_modify ( const char * data , gboolean add ) {
 GHashTable * optlist ;
 CHATNET_REC * chatnetrec ;
 CHANNEL_SETUP_REC * rec ;
 char * botarg , * botcmdarg , * chatnet , * channel , * password ;
 void * free_arg ;
 if ( ! cmd_get_params ( data , & free_arg , 3 | PARAM_FLAG_OPTIONS , "channel add" , & optlist , & channel , & chatnet , & password ) ) return ;
 if ( * chatnet == '\0' || * channel == '\0' ) {
 cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 }
 chatnetrec = chatnet_find ( chatnet ) ;
 if ( chatnetrec == NULL ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_UNKNOWN_CHATNET , chatnet ) ;
 cmd_params_free ( free_arg ) ;
 return ;
 }
 botarg = g_hash_table_lookup ( optlist , "bots" ) ;
 botcmdarg = g_hash_table_lookup ( optlist , "botcmd" ) ;
 rec = channel_setup_find ( channel , chatnet ) ;
 if ( rec == NULL ) {
 if ( add == FALSE ) {
 cmd_params_free ( free_arg ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CHANSETUP_NOT_FOUND , channel , chatnet ) ;
 return ;
 }
 rec = CHAT_PROTOCOL ( chatnetrec ) -> create_channel_setup ( ) ;
 rec -> name = g_strdup ( channel ) ;
 rec -> chatnet = g_strdup ( chatnet ) ;
 }
 else {
 if ( g_hash_table_lookup ( optlist , "bots" ) ) g_free_and_null ( rec -> botmasks ) ;
 if ( g_hash_table_lookup ( optlist , "botcmd" ) ) g_free_and_null ( rec -> autosendcmd ) ;
 if ( * password != '\0' ) g_free_and_null ( rec -> password ) ;
 }
 if ( g_hash_table_lookup ( optlist , "auto" ) ) rec -> autojoin = TRUE ;
 if ( g_hash_table_lookup ( optlist , "noauto" ) ) rec -> autojoin = FALSE ;
 if ( botarg != NULL && * botarg != '\0' ) rec -> botmasks = g_strdup ( botarg ) ;
 if ( botcmdarg != NULL && * botcmdarg != '\0' ) rec -> autosendcmd = g_strdup ( botcmdarg ) ;
 if ( * password != '\0' && g_strcmp0 ( password , "-" ) != 0 ) rec -> password = g_strdup ( password ) ;
 signal_emit ( "channel add fill" , 2 , rec , optlist ) ;
 channel_setup_create ( rec ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CHANSETUP_ADDED , channel , chatnet ) ;
 cmd_params_free ( free_arg ) ;
 }