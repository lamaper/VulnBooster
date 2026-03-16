void completion_last_message_rename ( const char * oldnick , const char * newnick ) {
 LAST_MSG_REC * rec ;
 g_return_if_fail ( oldnick != NULL ) ;
 g_return_if_fail ( newnick != NULL ) ;
 rec = last_msg_find ( global_lastmsgs , oldnick ) ;
 if ( rec != NULL ) {
 g_free ( rec -> nick ) ;
 rec -> nick = g_strdup ( newnick ) ;
 }
 }