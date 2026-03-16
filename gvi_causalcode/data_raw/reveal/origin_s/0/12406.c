GList * completion_msg ( SERVER_REC * win_server , SERVER_REC * find_server , const char * nick , const char * prefix ) {
 GSList * tmp , * list ;
 char * newprefix ;
 g_return_val_if_fail ( nick != NULL , NULL ) ;
 if ( servers == NULL ) return NULL ;
 list = NULL ;
 if ( find_server != NULL ) {
 completion_msg_server ( & list , find_server , nick , prefix ) ;
 return convert_msglist ( list ) ;
 }
 completion_msg_server ( & list , NULL , nick , prefix ) ;
 for ( tmp = servers ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 SERVER_REC * rec = tmp -> data ;
 if ( servers -> next == NULL && rec == win_server ) newprefix = g_strdup ( prefix ) ;
 else {
 newprefix = prefix == NULL ? g_strdup_printf ( "-%s" , rec -> tag ) : g_strdup_printf ( "%s -%s" , prefix , rec -> tag ) ;
 }
 completion_msg_server ( & list , rec , nick , newprefix ) ;
 g_free_not_null ( newprefix ) ;
 }
 return convert_msglist ( list ) ;
 }