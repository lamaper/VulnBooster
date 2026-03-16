static SERVER_SETUP_REC * create_server_setup ( GHashTable * optlist ) {
 CHAT_PROTOCOL_REC * rec ;
 SERVER_SETUP_REC * server ;
 char * chatnet ;
 rec = chat_protocol_find_net ( optlist ) ;
 if ( rec == NULL ) rec = chat_protocol_get_default ( ) ;
 else {
 chatnet = g_hash_table_lookup ( optlist , rec -> chatnet ) ;
 if ( chatnet_find ( chatnet ) == NULL ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_UNKNOWN_CHATNET , chatnet ) ;
 return NULL ;
 }
 }
 server = rec -> create_server_setup ( ) ;
 server -> chat_type = rec -> id ;
 return server ;
 }