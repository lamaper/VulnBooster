static void sig_server_disconnected ( SERVER_REC * server ) {
 MODULE_SERVER_REC * mserver ;
 g_return_if_fail ( server != NULL ) ;
 mserver = MODULE_DATA ( server ) ;
 while ( mserver -> lastmsgs ) last_msg_destroy ( & mserver -> lastmsgs , mserver -> lastmsgs -> data ) ;
 }