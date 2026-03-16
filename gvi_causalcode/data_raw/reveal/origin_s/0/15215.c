static void cmd_join ( const char * data , SERVER_REC * server ) {
 WINDOW_REC * window ;
 CHANNEL_REC * channel ;
 GHashTable * optlist ;
 char * pdata ;
 int invite ;
 int samewindow ;
 void * free_arg ;
 if ( ! cmd_get_params ( data , & free_arg , 1 | PARAM_FLAG_OPTIONS | PARAM_FLAG_UNKNOWN_OPTIONS | PARAM_FLAG_GETREST | PARAM_FLAG_STRIP_TRAILING_WS , "join" , & optlist , & pdata ) ) return ;
 invite = g_hash_table_lookup ( optlist , "invite" ) != NULL ;
 samewindow = g_hash_table_lookup ( optlist , "window" ) != NULL ;
 if ( ! invite && * pdata == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 server = cmd_options_get_server ( "join" , optlist , server ) ;
 channel = channel_find ( server , pdata ) ;
 if ( channel != NULL ) {
 window = window_item_window ( channel ) ;
 if ( window != active_win ) window_set_active ( window ) ;
 window_item_set_active ( active_win , ( WI_ITEM_REC * ) channel ) ;
 }
 else {
 if ( server == NULL || ! server -> connected ) cmd_param_error ( CMDERR_NOT_CONNECTED ) ;
 if ( invite ) {
 if ( server -> last_invite == NULL ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_NOT_INVITED ) ;
 signal_stop ( ) ;
 cmd_params_free ( free_arg ) ;
 return ;
 }
 pdata = server -> last_invite ;
 }
 if ( samewindow ) signal_add ( "channel created" , ( SIGNAL_FUNC ) signal_channel_created_curwin ) ;
 server -> channels_join ( server , pdata , FALSE ) ;
 if ( samewindow ) signal_remove ( "channel created" , ( SIGNAL_FUNC ) signal_channel_created_curwin ) ;
 }
 cmd_params_free ( free_arg ) ;
 }