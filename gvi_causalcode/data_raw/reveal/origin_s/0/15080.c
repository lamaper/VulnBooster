void completion_last_message_remove ( const char * nick ) {
 LAST_MSG_REC * rec ;
 g_return_if_fail ( nick != NULL ) ;
 rec = last_msg_find ( global_lastmsgs , nick ) ;
 if ( rec != NULL ) last_msg_destroy ( & global_lastmsgs , rec ) ;
 }