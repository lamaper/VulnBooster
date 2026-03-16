static void server_command ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 if ( server == NULL ) {
 server = active_win -> connect_server ;
 }
 signal_continue ( 3 , data , server , item ) ;
 }