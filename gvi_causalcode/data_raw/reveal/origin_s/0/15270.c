static void cmd_channel ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 if ( * data == '\0' ) cmd_channel_list_joined ( ) ;
 else if ( server != NULL && server_ischannel ( server , data ) ) {
 signal_emit ( "command join" , 3 , data , server , item ) ;
 }
 else {
 command_runsub ( "channel" , data , server , item ) ;
 }
 }