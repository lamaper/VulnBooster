static void cmd_cycle ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 CHANNEL_REC * chanrec ;
 char * channame , * msg , * joindata ;
 void * free_arg ;
 g_return_if_fail ( data != NULL ) ;
 if ( ! IS_SERVER ( server ) || ! server -> connected ) cmd_return_error ( CMDERR_NOT_CONNECTED ) ;
 if ( ! cmd_get_params ( data , & free_arg , 2 | PARAM_FLAG_OPTCHAN , item , & channame , & msg ) ) return ;
 if ( * channame == '\0' ) cmd_param_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 chanrec = channel_find ( server , channame ) ;
 if ( chanrec == NULL ) cmd_param_error ( CMDERR_CHAN_NOT_FOUND ) ;
 joindata = chanrec -> get_join_data ( chanrec ) ;
 window_bind_add ( window_item_window ( chanrec ) , chanrec -> server -> tag , chanrec -> name ) ;
 signal_emit ( "command part" , 3 , data , server , item ) ;
 if ( g_slist_find ( channels , chanrec ) != NULL ) {
 chanrec -> left = TRUE ;
 channel_destroy ( chanrec ) ;
 }
 server -> channels_join ( server , joindata , FALSE ) ;
 g_free ( joindata ) ;
 cmd_params_free ( free_arg ) ;
 }