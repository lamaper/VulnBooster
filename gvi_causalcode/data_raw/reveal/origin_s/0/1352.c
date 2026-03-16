static void cmd_names ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 CHANNEL_REC * chanrec ;
 GHashTable * optlist ;
 GString * unknowns ;
 char * channel , * * channels , * * tmp ;
 int flags ;
 void * free_arg ;
 g_return_if_fail ( data != NULL ) ;
 if ( ! IS_SERVER ( server ) || ! server -> connected ) cmd_return_error ( CMDERR_NOT_CONNECTED ) ;
 if ( ! cmd_get_params ( data , & free_arg , 1 | PARAM_FLAG_OPTIONS , "names" , & optlist , & channel ) ) return ;
 if ( g_strcmp0 ( channel , "*" ) == 0 || * channel == '\0' ) {
 if ( ! IS_CHANNEL ( item ) ) cmd_param_error ( CMDERR_NOT_JOINED ) ;
 channel = CHANNEL ( item ) -> name ;
 }
 flags = 0 ;
 if ( g_hash_table_lookup ( optlist , "ops" ) != NULL ) flags |= CHANNEL_NICKLIST_FLAG_OPS ;
 if ( g_hash_table_lookup ( optlist , "halfops" ) != NULL ) flags |= CHANNEL_NICKLIST_FLAG_HALFOPS ;
 if ( g_hash_table_lookup ( optlist , "voices" ) != NULL ) flags |= CHANNEL_NICKLIST_FLAG_VOICES ;
 if ( g_hash_table_lookup ( optlist , "normal" ) != NULL ) flags |= CHANNEL_NICKLIST_FLAG_NORMAL ;
 if ( g_hash_table_lookup ( optlist , "count" ) != NULL ) flags |= CHANNEL_NICKLIST_FLAG_COUNT ;
 if ( flags == 0 ) flags = CHANNEL_NICKLIST_FLAG_ALL ;
 unknowns = g_string_new ( NULL ) ;
 channels = g_strsplit ( channel , "," , - 1 ) ;
 for ( tmp = channels ;
 * tmp != NULL ;
 tmp ++ ) {
 chanrec = channel_find ( server , * tmp ) ;
 if ( chanrec == NULL ) g_string_append_printf ( unknowns , "%s," , * tmp ) ;
 else {
 fe_channels_nicklist ( chanrec , flags ) ;
 signal_stop ( ) ;
 }
 }
 g_strfreev ( channels ) ;
 if ( unknowns -> len > 1 ) g_string_truncate ( unknowns , unknowns -> len - 1 ) ;
 if ( unknowns -> len > 0 && g_strcmp0 ( channel , unknowns -> str ) != 0 ) signal_emit ( "command names" , 3 , unknowns -> str , server , item ) ;
 g_string_free ( unknowns , TRUE ) ;
 cmd_params_free ( free_arg ) ;
 }