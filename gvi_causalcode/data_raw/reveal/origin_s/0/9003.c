static void cmd_network ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 if ( * data == '\0' ) cmd_network_list ( ) ;
 else command_runsub ( "network" , data , server , item ) ;
 }