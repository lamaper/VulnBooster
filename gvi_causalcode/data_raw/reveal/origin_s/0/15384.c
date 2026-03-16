void completion_last_message_add ( const char * nick ) {
 g_return_if_fail ( nick != NULL ) ;
 last_msg_add ( & global_lastmsgs , nick , TRUE , keep_privates_count ) ;
 }