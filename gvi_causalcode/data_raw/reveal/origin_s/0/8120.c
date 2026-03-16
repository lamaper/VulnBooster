static void cmd_network_remove ( const char * data ) {
 IRC_CHATNET_REC * rec ;
 if ( * data == '\0' ) cmd_return_error ( CMDERR_NOT_ENOUGH_PARAMS ) ;
 rec = ircnet_find ( data ) ;
 if ( rec == NULL ) printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , IRCTXT_NETWORK_NOT_FOUND , data ) ;
 else {
 server_setup_remove_chatnet ( data ) ;
 channel_setup_remove_chatnet ( data ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , IRCTXT_NETWORK_REMOVED , data ) ;
 chatnet_remove ( CHATNET ( rec ) ) ;
 }
 }