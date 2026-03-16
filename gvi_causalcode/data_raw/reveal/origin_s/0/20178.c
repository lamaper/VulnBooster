static void cmd_channel_list ( void ) {
 GString * str ;
 GSList * tmp ;
 str = g_string_new ( NULL ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , TXT_CHANSETUP_HEADER ) ;
 for ( tmp = setupchannels ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 CHANNEL_SETUP_REC * rec = tmp -> data ;
 g_string_truncate ( str , 0 ) ;
 if ( rec -> autojoin ) g_string_append ( str , "autojoin, " ) ;
 if ( rec -> botmasks != NULL && * rec -> botmasks != '\0' ) g_string_append_printf ( str , "bots: %s, " , rec -> botmasks ) ;
 if ( rec -> autosendcmd != NULL && * rec -> autosendcmd != '\0' ) g_string_append_printf ( str , "botcmd: %s, " , rec -> autosendcmd ) ;
 if ( str -> len > 2 ) g_string_truncate ( str , str -> len - 2 ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , TXT_CHANSETUP_LINE , rec -> name , rec -> chatnet == NULL ? "" : rec -> chatnet , rec -> password == NULL ? "" : rec -> password , str -> str ) ;
 }
 g_string_free ( str , TRUE ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , TXT_CHANSETUP_FOOTER ) ;
 }